
#include <imgui.h>
#include <engine/log.hpp>
#include <engine/flecs.hpp>
#include <engine/debug/imgui.hpp>

#include "powernet.hpp"

void MetricsWindow(flecs::entity e) {
  bool is_open = true;
  ImGui::ShowMetricsWindow(&is_open);
  if (!is_open) {
    e.remove<engine::debug::ImGuiOpened>();
  }
}

void StyleEditor(flecs::entity e) {
  ImGui::ShowStyleEditor();
}

void DemoWindow(flecs::entity e) {
  bool is_open = true;
  ImGui::ShowDemoWindow(&is_open);
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
          ImGui::PushStyleColor(ImGuiCol_Button, {0.0f, 0.4f, 0.0f, 1.0f});
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

struct PowernetToolData {
  flecs::entity_t powernet_scope = flecs::entity::null();
  int powernets = 0;
  int consumers = 0;
  int producers = 0;
  int storages = 0;
  int powernet_type = 0;
};

void PowernetTool(flecs::entity e) {
  bool is_open = true;
  PowernetToolData* p_data = e.get_mut<PowernetToolData>();
  
  if (!ImGui::Begin("Powernet Tool", &is_open)) {
    ImGui::End();
    return;
  }

  if (!e.world().is_valid(p_data->powernet_scope)) {
    ImGui::Text("Has no scope entity");
    ImGui::End();
    return;
  }

  ImGui::DragInt("Powernets", &p_data->powernets, 2.0f);
  ImGui::DragInt("Consumers", &p_data->consumers, 2.0f);
  ImGui::DragInt("Producers", &p_data->producers, 2.0f);
  ImGui::DragInt("Storages", &p_data->storages, 2.0f);


  p_data->powernets = p_data->powernets > 0 ? p_data->powernets : 0;
  p_data->consumers = p_data->consumers > 0 ? p_data->consumers : 0;
  p_data->producers = p_data->producers > 0 ? p_data->producers : 0;
  p_data->storages = p_data->storages > 0 ? p_data->storages : 0;

  ImGui::RadioButton("Fast", &p_data->powernet_type, 0); ImGui::SameLine();
  ImGui::RadioButton("Normal", &p_data->powernet_type, 1); ImGui::SameLine();
  ImGui::RadioButton("Slow", &p_data->powernet_type, 2);


  if (ImGui::Button("Create")) {
    {
      flecs::scoped_world world = e.world().scope(p_data->powernet_scope);
      for (int powernet_i = 0; powernet_i < p_data->powernets; ++powernet_i) {
        flecs::entity powernet = world.entity()
          .add<game::powernet::Powernet>();
        switch (p_data->powernet_type) {
          case 0: {
            powernet.add<game::powernet::FastPowernetUpdate>();
            break;
          }
          case 2: {
            powernet.add<game::powernet::SlowPowernetUpdate>();
            break;
          }        
        }

        for (int consumers_i = 0; consumers_i < p_data->consumers; ++consumers_i) {
          flecs::entity consumer = world.entity()
            .set<game::powernet::Consumer>({.power = 1})
            .add<game::powernet::Link>(powernet)
            .child_of(powernet);
        }
        for (int producers_i = 0; producers_i < p_data->producers; ++producers_i) {
          flecs::entity producer = world.entity()
            .set<game::powernet::Producer>({.power = 1})
            .add<game::powernet::Link>(powernet)
            .child_of(powernet);
        }
        for (int storages_i = 0; storages_i < p_data->storages; ++storages_i) {
          flecs::entity storage = world.entity()
            .add<game::powernet::EnergyStorage>()
            .add<game::powernet::Link>(powernet)
            .child_of(powernet);
        }
      }
    }

  }

  ImGui::SameLine();

  if (ImGui::Button("Cleanup")) {
    e.world().filter_builder()
      .with<game::powernet::Powernet>().or_()
      .with<game::powernet::Producer>().or_()
      .with<game::powernet::Consumer>().or_()
      .with<game::powernet::EnergyStorage>()
      .build()
      .each([](flecs::entity e) {
        e.destruct();
      });
  }
  
  ImGui::End();
  if (!is_open) {
    e.remove<engine::debug::ImGuiOpened>();
  }
}



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

  world.entity("imgui_tools::style_editor")
    .set<engine::debug::ImGuiDebugTool>({.name = "Style Editor"})
    .set<engine::debug::ImGuiWindow>({.show_func = StyleEditor});

  world.entity("imgui_tools::demo")
    .set<engine::debug::ImGuiDebugTool>({.name = "Demo"})
    .set<engine::debug::ImGuiWindow>({.show_func = DemoWindow});

  ////////////////////////////////////////////////////////////////
  world.import<game::Powernet>();
  world.component<PowernetToolData>();

  flecs::entity powernet_scope = world.entity("powernet_scope").set_doc_color("#DD00DD");
  world.entity("imgui_tools::powernet_tool")
    .set<engine::debug::ImGuiDebugTool>({.name = "Powernet Tool"})
    .set<engine::debug::ImGuiWindow>({.show_func = PowernetTool})
    .set<PowernetToolData>({
      .powernet_scope = powernet_scope
    });

}

