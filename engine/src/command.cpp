#include <flecs.h>
#include <engine/command.hpp>
#include "modules.hpp"

namespace engine::command {

} //end of namespace engine::command


engine::CommandModule::CommandModule(flecs::world& world) {
  using namespace command;
  world.module<CommandModule>
  ("command");

  //components
  world.component<PhaseProcessCommandsPre>()
    .add(flecs::Phase)
    .depends_on(flecs::OnLoad);

  world.component<PhaseProcessCommands>()
    .add(flecs::Phase)
    .depends_on<PhaseProcessCommandsPre>();

  world.component<Handle>()
    .add(flecs::Tag);

  world.component<Supress>()
    .add(flecs::Tag);

  world.component<Emit>()
    .add(flecs::Tag);

  world.component<On>()
    .add(flecs::Tag);

  world.component<ConnectionNext>()
    .add(flecs::Tag);

  world.component<ConnectionPrev>()
    .add(flecs::Tag);

  world.component<Command>();

  world.component<Category>()
    .add(flecs::Tag);

  //systems
}