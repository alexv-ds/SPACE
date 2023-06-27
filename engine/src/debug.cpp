#include <engine/debug/imgui.hpp>
#include <engine/lib/log.hpp>
#include "debug.hpp"

namespace engine::debug {

void ShowImguiWindow(flecs::entity e, const ImGuiWindow& window) {
  if (window.show_func) {
    window.show_func(e);
  }
}

} //namespace engine::debug

engine::Debug::Debug(flecs::world& world) {
  using namespace debug;
  world.module<Debug>("debug");

  //components
  world.component<ImGuiContext>();
  world.component<ImGuiWindow>();
  world.component<ImGuiOpened>();
  world.component<ImGuiDebugTool>();

  //systems
  world.system<const ImGuiWindow>("system::ShowImguiWindow")
    .kind(flecs::OnStore)
    .with<ImGuiContext>().singleton()
    .with<ImGuiOpened>()
    .each(ShowImguiWindow);
}