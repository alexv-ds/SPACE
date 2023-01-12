#include <cmath>
#include <spdlog/spdlog.h>
#include "powernet.hpp"

namespace game::powernet::detail {

void CleanupPowernetLastFrameData(flecs::iter it, Powernet* powernet) {
  for (auto i : it) {
    powernet[i].power_consumption = 0;
    powernet[i].power_generation = 0;
    powernet[i].on_frame_power_usage = 0;
  }
}

void UpdateConsumers(flecs::iter it, Powernet* powernet, const Consumer* consumer) {
  for (auto i : it) {
    powernet[i].on_frame_power_usage += consumer[i].power;
    flecs::entity e = it.entity(i);
    if (powernet[i].on_frame_power_usage > powernet[i].power_generation) {
      it.entity(i).remove<Powerized>();
    } else {
      it.entity(i).add<Powerized>();
    }
  }
}

void UpdateConsumers2(flecs::iter it, Powernet* powernet, const Consumer* consumer, const Powerized* powerized) {
  //че-та сложна для пониманеия нахой
  //мб переписать?
  if (powernet->on_frame_power_usage > powernet->power_generation) {
    if (powerized) {
      for (auto i : it) {
        it.entity(i).remove<Powerized>();
      }
    }
  } else {
    if (powerized) {
      for (auto i : it) {
        powernet->on_frame_power_usage += consumer[i].power;
        if (powernet->on_frame_power_usage > powernet->power_generation) {
          it.entity(i).remove<Powerized>();
        }
      }
    } else {
      for (auto i : it) {
        powernet->on_frame_power_usage += consumer[i].power;
        if (powernet->on_frame_power_usage <= powernet->power_generation) {
          it.entity(i).add<Powerized>();
        }
      }
    }
  }
}

void GeneratePower(flecs::iter it, powernet::Powernet* powernet, const powernet::Producer* producer) {
  for (auto i : it) {
    powernet[i].power_generation += producer[i].power;
  }
}

} //namespace game::powernet::detail

namespace game {

Powernet::Powernet(flecs::world& world) {
  //world.import<flecs::Timer>();
  world.import<flecs::units>();
  world.module<Powernet>("powernet");

  world.component<powernet::Powernet>()
    .member<float>("power_consumption")
    .member<float>("power_generation")
    .member<float>("on_frame_power_usage");
  world.component<powernet::Consumer>()
    .member<float>("power");
  world.component<powernet::Producer>()
    .member<float>("power");
  world.component<powernet::Link>()
    .add(flecs::Acyclic);
  world.component<powernet::Powerized>();
  world.component<powernet::Disabled>();
  world.component<powernet::EnergyStorage>()
    .member<float>("min_output_power")
    .member<float>("max_output_power")
    .member<float>("input_power")
    .member<float>("energy")
    .member<float>("max_energy")
    .member<float>("last_update_output_power")
    .member<float>("last_update_input_power");
  
  //observers
  
  //systems
  world.system<powernet::Powernet>("system::CleanupPowernetLastFrameData")
    .multi_threaded()
    .iter(powernet::detail::CleanupPowernetLastFrameData);

  world.system<powernet::Powernet, const powernet::Producer>("system::GeneratePower")
    .multi_threaded()
    .term_at(1).up<powernet::Link>()
    .without<powernet::Disabled>()
    //.instanced()
    .iter(powernet::detail::GeneratePower);
    //.each([](flecs::entity e, powernet::Powernet& powernet, const powernet::Producer producer) {
    //  powernet.power_generation += producer.power;
    //});
    
  world.system<powernet::Powernet, const powernet::Consumer>("system::ConsumePower")
    .multi_threaded()
    .term_at(1).up<powernet::Link>()
    .without<powernet::Disabled>()
    .each([](flecs::entity e, powernet::Powernet& powernet, const powernet::Consumer consumer) {
      powernet.power_consumption += consumer.power;
    });

  world.system<powernet::Powernet, powernet::EnergyStorage>("system::UpdateEnergyStorages")
    .multi_threaded()
    .term_at(1).up<powernet::Link>()
    .without<powernet::Disabled>()
    .each([](flecs::entity e, powernet::Powernet& powernet, powernet::EnergyStorage& storage) {
      storage.energy += e.delta_time() * storage.last_update_input_power;
      storage.energy -= e.delta_time() * storage.last_update_output_power;
      storage.last_update_input_power = 0;
      storage.last_update_output_power = 0;

      const float power_excess = powernet.power_generation - powernet.power_consumption;
      //зарядка
      if (power_excess > 0 && storage.energy < storage.max_energy) {
        storage.last_update_input_power = power_excess > storage.input_power ? storage.input_power : power_excess;
      //разрядка
      } else if (power_excess < 0 && storage.energy > 0) {
        float needs_powed = std::abs(power_excess);
        if (needs_powed > storage.max_output_power) {
          storage.last_update_output_power = storage.max_output_power;
        } else if (needs_powed < storage.min_output_power) {
          storage.last_update_output_power = storage.min_output_power;
        } else {
          storage.last_update_output_power = needs_powed;
        }
        powernet.power_generation += storage.last_update_output_power;
      }
    });

  world.system<powernet::Powernet, const powernet::Consumer>("system::UpdateConsumers")
    .multi_threaded()
    .term_at(1).up<powernet::Link>()
    .with<powernet::Powerized>().optional().inout()
    .without<powernet::Disabled>()
    .iter(powernet::detail::UpdateConsumers);

  /*world.system<powernet::Powernet, const powernet::Consumer, const powernet::Powerized>("system::UpdateConsumers")
    .multi_threaded()
    .instanced()
    .term_at(1).up<powernet::Link>()
    .term_at(3).optional().inout()
    .without<powernet::Disabled>()
    .iter(powernet::detail::UpdateConsumers2);*/
}

} //namespace game