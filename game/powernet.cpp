#include "powernet.hpp"

namespace game {

Powernet::Powernet(flecs::world& world) {
  //world.import<flecs::Timer>();
  world.module<Powernet>("powernet");


}

} //namespace game