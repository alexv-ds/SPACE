#include <random>
#include <format>
#include <spdlog/spdlog.h>
#include <flecs.h>
#include "../engine/setup_spdlog.hpp"
#include "powernet.hpp"

using namespace game;

int main() {
  engine::setup_spdlog();
  flecs::world world;
  //world.set_threads(4);
  world.set_target_fps(60);
  world.import<flecs::monitor>(); 
  world.import<game::Powernet>();

  std::random_device rd;
  std::mt19937 mt(rd());

  std::uniform_int_distribution<int> powernet_count(1000,1001);

  std::uniform_int_distribution<int> consumer_count(1000,1100);
  std::uniform_real_distribution<float> counsumers_power(1,2);

  std::uniform_int_distribution<int> producer_count(1000,1100);
  std::uniform_real_distribution<float> producers_power(1,2);

  std::uniform_int_distribution<int> storage_count(1000,1100);
  std::uniform_real_distribution<float> storage_min_output_power(0,1);
  std::uniform_real_distribution<float> storage_max_output_power(1,5);
  std::uniform_real_distribution<float> storage_imput_power(1,3);
  std::uniform_real_distribution<float> storage_max_energy(10,500);


  int i_powernet_count = powernet_count(mt);
  for (int i_powernet = 0; i_powernet < i_powernet_count; ++i_powernet) {
    flecs::entity powernet = world.entity()
      .set_doc_name(std::format("powernet-{}", i_powernet).c_str())
      .add<powernet::Powernet>();
  
    int i_producer_count = producer_count(mt);
    for (int i_producer = 0; i_producer < i_producer_count; ++i_producer) {
      static int producer_id = 0;
      flecs::entity producer = world.entity()
        .set_doc_name(std::format("producer-{}", producer_id++).c_str())
        .set<powernet::Producer>({.power=producers_power(mt)})
        .add<powernet::Link>(powernet)
        .child_of(powernet);
    }

    int i_consumers_count = consumer_count(mt);
    for (int i_consumer = 0; i_consumer < i_consumers_count; ++i_consumer) {
      static int consumer_id = 0;
      flecs::entity consumer = world.entity()
        .set_doc_name(std::format("consumer-{}", consumer_id++).c_str())
        .set<powernet::Consumer>({.power=counsumers_power(mt)})
        .add<powernet::Link>(powernet)
        .child_of(powernet);
    }

    int i_storage_count = storage_count(mt);
    for (int i_storage = 0; i_storage < i_storage_count; ++i_storage) {
      static int storage_id = 0;
      flecs::entity storage = world.entity()
        .set_doc_name(std::format("storage-{}", storage_id++).c_str())
        .set<powernet::EnergyStorage>({
          .min_output_power = storage_min_output_power(mt),
          .max_output_power = storage_max_output_power(mt),
          .input_power = storage_imput_power(mt),
          .max_energy = storage_max_energy(mt)
        })
        .add<powernet::Link>(powernet)
        .child_of(powernet);
    }


  }
  

  /*flecs::entity powernet = world.entity("powernet")
    .add<powernet::Powernet>();

  flecs::entity consumer = world.entity("consumer")
    .set<powernet::Consumer>({.power=3.33f})
    .add<powernet::Link>(powernet);

  flecs::entity produser = world.entity("produser")
    .set<powernet::Producer>({.power=3.33f})
    .add<powernet::Link>(powernet);

  flecs::entity energy_storage = world.entity("energy_storage")
    .set<powernet::EnergyStorage>({
      .energy = 0,
      .max_energy = 100
    })
    .add<powernet::Link>(powernet);
  */

  world.app().enable_rest().run();
}