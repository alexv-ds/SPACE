#include "filesystem.hpp"

namespace engine {
using namespace engine::filesystem;

Filesystem::Filesystem(flecs::world& world) {
  world.module<Filesystem>("filesystem");

  world.component<ReadFileRequest>();
  world.component<ReadFileResponse>();
}

} //namespace engine