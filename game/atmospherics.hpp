#pragma once
#include <flecs.h>

namespace game {

struct Atmospherics {
  Atmospherics(flecs::world&);
};

} //namespace game

namespace game::atmospherics {

struct Zone {
  float volume = 1; //m^3
  float energy = 0; //J

  //auto calculated
  float temperature; //in Kelvins
  float pressure; //Pa
};

struct GasData {
  float amount;
};

} //namespace game::atmospherics