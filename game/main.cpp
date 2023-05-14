
#include <imgui.h>
#include <engine/log.hpp>
#include <engine/flecs.hpp>
#include <engine/debug/imgui.hpp>

/*void ShowImgui(flecs::iter it) {
  ImGui::ShowMetricsWindow();
}*/

void MetricsWindow(flecs::entity e) {
  bool is_open = true;
  ImGui::ShowMetricsWindow(&is_open);
  if (!is_open) {
    e.remove<engine::debug::ImGuiOpened>();
  }
}

void DebugTools(flecs::entity e) {
  if (ImGui::Begin("Debug Tools")) {
    e.world().filter_builder<const engine::debug::ImGuiDebugTool>()
      .build()
      .each([](flecs::entity tool_entity, const engine::debug::ImGuiDebugTool& tool) {
        bool tool_active = tool_entity.has<engine::debug::ImGuiOpened>();
        if (tool_active) {
          ImGui::PushStyleColor(ImGuiCol_Button, {0.0, 0.4, 0.0, 1.0});
        }
        if (ImGui::Button(tool.name.c_str(), {200,0})) {
          if (tool_entity.has<engine::debug::ImGuiOpened>()) {
            tool_entity.remove<engine::debug::ImGuiOpened>();
          } else {
            tool_entity.add<engine::debug::ImGuiOpened>();
          }
        }
        if (tool_active) {
          ImGui::PopStyleColor();
        }
      });
  }
  ImGui::End();
};



void engine_main(flecs::world& world) {
  world.set<flecs::Rest>({});
  world.import<flecs::monitor>();

  world.entity("imgui_tools").set_doc_color("#DD00DD");

  world.entity("imgui_tools::metric_window")
    .set<engine::debug::ImGuiDebugTool>({.name = "Metrics"})
    .set<engine::debug::ImGuiWindow>({.show_func = MetricsWindow});

  world.entity("imgui_tools::debug_tools")
    .add<engine::debug::ImGuiOpened>()
    .set<engine::debug::ImGuiWindow>({.show_func = DebugTools});

}

