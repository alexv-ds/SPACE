#include <cmath>
#include <spdlog/spdlog.h>
#include "powernet.hpp"

namespace game::powernet::detail {

static void CleanupPowernetLastFrameData(flecs::iter it, Powernet* powernet) {
  if (it.is_self(1)) [[likely]] {
    for (auto i : it) {
      powernet[i].power_consumption = 0;
      powernet[i].power_generation = 0;
      powernet[i].on_frame_power_usage = 0;
    }
  } else [[unlikely]] {
    powernet->power_consumption = 0;
    powernet->power_generation = 0;
    powernet->on_frame_power_usage = 0;
  }
}

static inline void GeneratePower(flecs::entity e, powernet::Powernet& powernet, const powernet::Producer& producer) {
  powernet.power_generation += producer.power;
}

static inline void ConsumePower(flecs::entity e, powernet::Powernet& powernet, const powernet::Consumer& consumer) {
  powernet.power_consumption += consumer.power;
}

static inline void UpdateConsumers(flecs::iter it, Powernet* powernet, const Consumer* consumer) {
  bool is_powerized = it.is_set(3); //3й аргумент - .with<powernet::Powerized>().optional().inout()
  for (auto i : it) {
    powernet[i].on_frame_power_usage += consumer[i].power;
    if (powernet[i].on_frame_power_usage > powernet[i].power_generation) {
      if (is_powerized) {
        it.entity(i).remove<Powerized>();
      }
    } else {
      if (!is_powerized) {
        it.entity(i).add<Powerized>();
      }
    }
  }
}

static inline void UpdateEnergyStorages(flecs::entity e, Powernet& powernet, EnergyStorage& storage) {
  storage.energy -= e.delta_time() * storage.last_update_power;

  const float power_excess = powernet.power_generation - powernet.power_consumption;
  //зарядка
  if (power_excess > 0 && storage.energy < storage.max_energy) {
    storage.last_update_power = -(power_excess > storage.input_power ? storage.input_power : power_excess);
  //разрядка
  } else if (power_excess < 0 && storage.energy > 0) {
    float needs_powed = std::abs(power_excess);
    if (needs_powed > storage.max_output_power) {
      storage.last_update_power = storage.max_output_power;
    } else if (needs_powed < storage.min_output_power) {
      storage.last_update_power = storage.min_output_power;
    } else {
      storage.last_update_power = needs_powed;
    }
    powernet.power_generation += storage.last_update_power;
  }
}

static inline void ObserverOnSet_Disabled(flecs::entity e) {
  e.remove<Powerized>();
}

template<class T = void>
static void create_systems_set(flecs::entity_t tick_source) {

}

} //namespace game::powernet::detail

namespace game {

Powernet::Powernet(flecs::world& world) {
  world.import<flecs::units>();
  world.module<Powernet>("powernet");

  //components
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
    .member<float>("last_update_power");
  
  //init tick sources
  flecs::entity timer_scope = world.entity("timer");
  this->normal_powernet_tick_source = world.timer()
    .interval(1.0f / 5.0f) //5 Hz
    .set_name("normal_powernet_tick_source")
    .child_of(timer_scope);
  this->slow_powernet_tick_source = world.timer()
    .rate(5, normal_powernet_tick_source) //1 HZ
    .set_name("slow_powernet_tick_source")
    .child_of(timer_scope);

  //observer
  flecs::entity observer_scope = world.entity("observer");
  world.observer()
    .event(flecs::OnSet)
    .with<powernet::Disabled>()
    .with<powernet::Powerized>()
    .each(powernet::detail::ObserverOnSet_Disabled)
    .set_name("ObserverOnSet_Disabled")
    .child_of(observer_scope);
  
  //systems
  world.system<powernet::Powernet>("system::CleanupPowernetLastFrameData")
    .instanced()
    .iter(powernet::detail::CleanupPowernetLastFrameData);

  world.system<powernet::Powernet, const powernet::Producer>("system::GeneratePower")
    .arg(1).up<powernet::Link>()
    .without<powernet::Disabled>()
    .each(powernet::detail::GeneratePower);
    
  world.system<powernet::Powernet, const powernet::Consumer>("system::ConsumePower")
    .term_at(1).up<powernet::Link>()
    .without<powernet::Disabled>()
    .each(powernet::detail::ConsumePower);

  world.system<powernet::Powernet, powernet::EnergyStorage>("system::UpdateEnergyStorages")
    .term_at(1).up<powernet::Link>()
    .without<powernet::Disabled>()
    .each(powernet::detail::UpdateEnergyStorages);

  world.system<powernet::Powernet, const powernet::Consumer>("system::UpdateConsumers")
    .arg(1).up<powernet::Link>()
    .with<powernet::Powerized>().optional().inout()
    .without<powernet::Disabled>()
    .iter(powernet::detail::UpdateConsumers);

  powernet::detail::create_systems_set<powernet::SlowPowernetUpdate>(this->slow_powernet_tick_source);
  powernet::detail::create_systems_set(this->normal_powernet_tick_source);
  powernet::detail::create_systems_set<powernet::FastPowernetUpdate>(0); //every frame
}

} //namespace game