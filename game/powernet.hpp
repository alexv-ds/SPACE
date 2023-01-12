#pragma once
#include <limits>
#include <flecs.h>

namespace game {

struct Powernet {
  flecs::entity_t update_tick_source;

  Powernet(flecs::world&);
};

} //namespace game

namespace game::powernet {

struct Powernet {
  float power_consumption = 0; //Watt
  float power_generation = 0; //Watt

  //internal
  //Каждый потребитель энергии добавляет свое значение потребления каждое обновление сети
  //Если on_frame_power_usage становится больше power_generation, то потребитель и остальные потребители
  //Лишаются компонента Powerized
  float on_frame_power_usage = 0; //Watt
};

struct Consumer {
  float power = 0; //Watt
};
struct Producer {
  float power = 0; //Watt
};

struct EnergyStorage {
  float min_output_power = 0;
  float max_output_power = std::numeric_limits<float>::infinity();
  float input_power = std::numeric_limits<float>::infinity();
  //может быть отрицательным. Значит то, что из батарейки взяли больше, чем в ней было, кек
  //Не беда, вселенский балланс востановим когда заряжать будем
  float energy = 0; 
  float max_energy = std::numeric_limits<float>::infinity();

  //internal
  float last_update_output_power = 0;
  float last_update_input_power = 0;
};

struct Link {};

struct Powerized {};

struct Disabled {};

//struct EnergyStore {
//  float max_power; //Watt
//  float energy; //J
//};

} //namespace game::powernet