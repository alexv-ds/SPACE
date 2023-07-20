#pragma once
#include <vector>
#include <string>
#include <flecs.h>
#include <engine/lib/log.hpp>

namespace test {

void disable_all(flecs::world& world, const std::vector<std::string>& exclude = {}) {
  std::vector<flecs::entity> systems;
  world.filter_builder()
    .with(flecs::System)
    .each([&systems](flecs::entity e) {
      systems.push_back(e);
    });

  for(auto system : systems) {
    system.add(flecs::Disabled);
  }

  for(auto entity_name : exclude) {
    flecs::entity entity = world.lookup(entity_name.c_str());
    if (entity == flecs::entity::null()) {
      ENGINE_WARN("Excluded entity not exists - {}", entity_name);
      continue;
    }
    entity.remove(flecs::Disabled);
  }
}

}