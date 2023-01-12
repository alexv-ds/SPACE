#pragma once
#include <flecs.h>

namespace game {

struct Powernet {
  flecs::entity_t update_tick_source;

  Powernet(flecs::world&);
};

} //namespace game

namespace game::powernet {

struct Powernet {
  float power_consumption = 0;
  float power_generation = 0;
};

struct Consumer {
  float power = 0; //Watt
};
struct Producer {
  float power = 0; //Watt
};

struct Link {};

//struct EnergyStore {
//  float max_power; //Watt
//  float energy; //J
//};

} //namespace game::powernet