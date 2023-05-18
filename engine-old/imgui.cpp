#include "imgui.hpp"

engine::Imgui::Imgui(flecs::world& world) {
  world.module<Imgui>("imgui");
  world.component<imgui::ImguiContext>();
}