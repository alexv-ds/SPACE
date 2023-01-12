#include <format>
#include <spdlog/spdlog.h>
#include <flecs.h>
#include "../engine/setup_spdlog.hpp"
#include "powernet.hpp"

using namespace game;

int main() {
  engine::setup_spdlog();
  flecs::world world;
  world.set_threads(4);
  world.set_target_fps(60);
  world.import<flecs::monitor>(); 
  world.import<game::Powernet>();

  flecs::entity scope = world.entity("scope");
  flecs::entity prev_scope = world.set_scope(scope);

  for(int i_powernet = 0; i_powernet < 1; ++i_powernet) {
    SPDLOG_INFO("Create powernet - {}", i_powernet);
    flecs::entity powernet = world.entity()
      //.set_doc_name(std::format("powernet-{}", i_powernet).c_str())
      .add<powernet::Powernet>();
    for (int i_consumer = 0; i_consumer <= 1000; ++i_consumer) {
      flecs::entity consumer = world.entity()
        //.set_doc_name(std::format("consumer-{}", i_consumer).c_str())
        .set<powernet::Consumer>({.power=0.35f})
        .add<powernet::Link>(powernet)
        .child_of(powernet);
    }
    for (int i_producer = 0; i_producer <= 1000; ++i_producer) {
      flecs::entity producer = world.entity()
        //.set_doc_name(std::format("producer-{}", i_producer).c_str())
        .set<powernet::Producer>({.power=0.35f})
        .add<powernet::Link>(powernet)
        .child_of(powernet);
    }
    for (int i_storage = 0; i_storage <= 1000; ++i_storage) {
      flecs::entity storage = world.entity()
        //.set_doc_name(std::format("storage-{}", i_storage).c_str())
        .set<powernet::EnergyStorage>({.max_energy=10.0f})
        .add<powernet::Link>(powernet)
        .child_of(powernet);
    }
  }

  world.set_scope(prev_scope);

  world.app().enable_rest().run();
}