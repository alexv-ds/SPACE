#include <cstdint>
#include <flecs.h>
#include <engine/command.hpp>
#include <engine/lib/log.hpp>
#include "modules.hpp"

namespace engine::command {

static void OnAdd_ConnectionNext(flecs::iter it, std::size_t i) {
  ENGINE_TRACE("OnAdd_ConnectionNext");
  flecs::entity first = it.entity(i);
  flecs::entity second = it.pair(1).second();
  if (!second.has<ConnectionPrev>(first)) {
    second.add<ConnectionPrev>(first);
  }
}

static void OnAdd_ConnectionPrev(flecs::iter it, std::size_t i) {
  ENGINE_TRACE("OnAdd_ConnectionPrev");
  flecs::entity first = it.entity(i);
  flecs::entity second = it.pair(1).second();
  if (!second.has<ConnectionNext>(first)) {
    second.add<ConnectionNext>(first);
  }
}

static void EmitCommand(flecs::iter it, const Emit*) {
  for (auto i : it) {
    flecs::world world = it.world();
    flecs::entity entity = it.entity(i);
    flecs::entity second = it.pair(1).second();
    ENGINE_WARN("{}", second.path().c_str());
    //const void* data_ptr = entity.get<Emit>();
    ENGINE_WARN("{}", entity.has<Emit>(second));

    void* const data_ptr = entity.get_mut(world.entity<Emit>(), second);
    flecs::cursor cursor = world.cursor(second, data_ptr);

    flecs::untyped_component component(second);


    entity.remove<Emit>(second);
  }
}

} //end of namespace engine::command


engine::CommandModule::CommandModule(flecs::world& world) {
  using namespace command;
  world.module<CommandModule>("command");

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

  world.component<Emit>();

  world.component<On>()
    .add(flecs::Tag);

  world.component<ConnectionNext>()
    .add(flecs::Tag);

  world.component<ConnectionPrev>()
    .add(flecs::Tag);

  world.component<Command>();

  world.component<Category>()
    .add(flecs::Tag);

  //observers
  {
    [[maybe_unused]] auto scope = world.scope(world.entity("observer"));
    world.observer("OnAdd_ConnectionNext")
      .event(flecs::OnAdd)
      .with<ConnectionNext>().second(flecs::Wildcard)
      .each(OnAdd_ConnectionNext);

    world.observer("OnAdd_ConnectionPrev")
      .event(flecs::OnAdd)
      .with<ConnectionPrev>().second(flecs::Wildcard)
      .each(OnAdd_ConnectionPrev);
  }

  //systems
  {
    [[maybe_unused]] auto scope = world.scope(world.entity("system"));
    world.system<const Emit>("EmitCommand")
      .kind<PhaseProcessCommands>()
      .arg(1).second(flecs::Wildcard)
      .iter(EmitCommand);
  }
}