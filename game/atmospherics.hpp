#pragma once
#include <flecs.h>

namespace game {

struct Atmospherics {
  Atmospherics(flecs::world&);
};

} //namespace game

namespace game::atmospherics {

struct GasMixture {
  float volume = 1; //m^3
  float energy = 0; //J

  //auto calculated
  float temperature; //in Kelvins
  float pressure; //Pa
  float specific_heat;
  float amount;
};

struct GasData {
  float amount;
  float specific_heat;
};

struct SpecificHeat {
  float value = 5193; //Гелий
};

} //namespace game::atmospherics