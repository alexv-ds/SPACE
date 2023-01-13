#include <cmath>
#include <type_traits>
#include <format>
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
static void create_systems_set(flecs::world& world, const flecs::entity_t tick_source, const char* speed_name) {
  //CleanupPowernetLastFrameData
  {
    flecs::entity cleanup_system_scope = world.entity("system::CleanupPowernetLastFrameData");
    flecs::system_builder cleanup_system = world.system<Powernet>(std::format("{}_CleanupPowernetLastFrameData", speed_name).c_str());

    cleanup_system.instanced();
    if constexpr (std::is_void_v<T>) {
      cleanup_system.without<SlowPowernetUpdate>();
      cleanup_system.without<FastPowernetUpdate>();
    } else  {
      if constexpr (std::is_same_v<T, FastPowernetUpdate>) {
        cleanup_system.with<FastPowernetUpdate>();
        cleanup_system.without<SlowPowernetUpdate>();
      } else {
        cleanup_system.with<SlowPowernetUpdate>();
        cleanup_system.without<FastPowernetUpdate>();
      }
    }
    if (tick_source) {
      cleanup_system.tick_source(tick_source);
    }
    cleanup_system
      .iter(CleanupPowernetLastFrameData)
      .child_of(cleanup_system_scope);
  }

  //GeneratePower
  {
    flecs::entity generate_system_scope = world.entity("system::GeneratePower");
    flecs::system_builder generate_system = world.system<Powernet, const Producer>(std::format("{}_GeneratePower", speed_name).c_str());

    generate_system.arg(1).up<Link>();
    generate_system.without<Disabled>();
    if constexpr (std::is_void_v<T>) {
      generate_system.without<SlowPowernetUpdate>().up<Link>();
      generate_system.without<FastPowernetUpdate>().up<Link>();
    } else {
      if constexpr (std::is_same_v<T, FastPowernetUpdate>) {
        generate_system.with<FastPowernetUpdate>().up<Link>();
        generate_system.without<SlowPowernetUpdate>().up<Link>();
      } else {
        generate_system.with<SlowPowernetUpdate>().up<Link>();
        generate_system.without<FastPowernetUpdate>().up<Link>();
      }
    }
    if (tick_source) {
      generate_system.tick_source(tick_source);
    }
    generate_system
      .each(GeneratePower)
      .child_of(generate_system_scope);
  }

  //ConsumePower
  {
    flecs::entity consume_system_scope = world.entity("system::ConsumePower");
    flecs::system_builder consume_system = world.system<Powernet, const Consumer>(std::format("{}_ConsumePower", speed_name).c_str());

    consume_system.term_at(1).up<Link>();
    consume_system.without<Disabled>();
    if constexpr (std::is_void_v<T>) {
      consume_system.without<SlowPowernetUpdate>().up<Link>();
      consume_system.without<FastPowernetUpdate>().up<Link>();
    } else {
      if constexpr (std::is_same_v<T, FastPowernetUpdate>) {
        consume_system.with<FastPowernetUpdate>().up<Link>();
        consume_system.without<SlowPowernetUpdate>().up<Link>();
      } else {
        consume_system.with<SlowPowernetUpdate>().up<Link>();
        consume_system.without<FastPowernetUpdate>().up<Link>();
      }
    }
    if (tick_source) {
      consume_system.tick_source(tick_source);
    }
    consume_system
      .each(ConsumePower)
      .child_of(consume_system_scope);
  }

  //UpdateEnergyStorages
  {
    flecs::entity storages_system_scope = world.entity("system::UpdateEnergyStorages");
    flecs::system_builder storages_system = world.system<Powernet, EnergyStorage>(std::format("{}_UpdateEnergyStorages", speed_name).c_str());

    storages_system.arg(1).up<Link>();
    storages_system.without<Disabled>();
    if constexpr (std::is_void_v<T>) {
      storages_system.without<SlowPowernetUpdate>().up<Link>();
      storages_system.without<FastPowernetUpdate>().up<Link>();
    } else {
      if constexpr (std::is_same_v<T, FastPowernetUpdate>) {
        storages_system.with<FastPowernetUpdate>().up<Link>();
        storages_system.without<SlowPowernetUpdate>().up<Link>();
      } else {
        storages_system.with<SlowPowernetUpdate>().up<Link>();
        storages_system.without<FastPowernetUpdate>().up<Link>();
      }
    }
    if (tick_source) {
      storages_system.tick_source(tick_source);
    }
    storages_system
      .each(UpdateEnergyStorages)
      .child_of(storages_system_scope);
  }

  //UpdateConsumers
  {
    flecs::entity update_consumers_system_scope = world.entity("system::UpdateConsumers");
    flecs::system_builder update_consumers_system = world.system<Powernet, const Consumer>(std::format("{}_UpdateConsumers", speed_name).c_str());

    update_consumers_system.arg(1).up<Link>();
    update_consumers_system.with<Powerized>().optional().inout();
    update_consumers_system.without<Disabled>();
    if constexpr (std::is_void_v<T>) {
      update_consumers_system.without<SlowPowernetUpdate>().up<Link>();
      update_consumers_system.without<FastPowernetUpdate>().up<Link>();
    } else {
      if constexpr (std::is_same_v<T, FastPowernetUpdate>) {
        update_consumers_system.with<FastPowernetUpdate>().up<Link>();
        update_consumers_system.without<SlowPowernetUpdate>().up<Link>();
      } else {
        update_consumers_system.with<SlowPowernetUpdate>().up<Link>();
        update_consumers_system.without<FastPowernetUpdate>().up<Link>();
      }
    }
    if (tick_source) {
      update_consumers_system.tick_source(tick_source);
    }
    update_consumers_system
      .iter(powernet::detail::UpdateConsumers)
      .child_of(update_consumers_system_scope);
  }  
}

static void register_components(flecs::world& world) {
  world.component<Powernet>()
    .member<float>("power_consumption")
    .member<float>("power_generation")
    .member<float>("on_frame_power_usage");

  world.component<Consumer>()
    .member<float>("power");

  world.component<Producer>()
    .member<float>("power");

  world.component<Link>()
    .add(flecs::Acyclic);

  world.component<Powerized>();
  world.component<Disabled>();

  world.component<EnergyStorage>()
    .member<float>("min_output_power")
    .member<float>("max_output_power")
    .member<float>("input_power")
    .member<float>("energy")
    .member<float>("max_energy")
    .member<float>("last_update_power");

  world.component<SlowPowernetUpdate>();
  world.component<FastPowernetUpdate>();
}

} //namespace game::powernet::detail

namespace game {

Powernet::Powernet(flecs::world& world) {
  world.import<flecs::units>();
  world.module<Powernet>("powernet");

  //components
  powernet::detail::register_components(world);
  
  //init tick sources
  flecs::entity timer_scope = world.entity("timer");
  this->normal_powernet_tick_source = world.timer()
    .interval(1.0f / 5.0f) //5 Hz
    .set_name("normal_powernet_tick_source")
    .child_of(timer_scope);
  this->slow_powernet_tick_source = world.timer()
    .interval(1.0f) //1 Hz
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
  powernet::detail::create_systems_set<powernet::SlowPowernetUpdate>(world, this->slow_powernet_tick_source, "slow");
  powernet::detail::create_systems_set(world, this->normal_powernet_tick_source, "normal");
  powernet::detail::create_systems_set<powernet::FastPowernetUpdate>(world, 0, "fast"); //every frame
}

} //namespace game