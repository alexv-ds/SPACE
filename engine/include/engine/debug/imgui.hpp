#pragma once
#include <functional>
#include <string>
#include <flecs.h>

/** \addtogroup engine-debug 
 *  @{
 */

namespace engine::debug {

/**
 * @brief Синглтон компонент. Характеризует доступность ImGui контекста.
 * 
 * При наличии контекста ImGui можно использовать функции библиотеки.
 */
struct ImGuiContext {};

struct ImGuiWindow {
  std::function<void(flecs::entity)> show_func; ///< функция отображения imgui окна
};

/// @brief Компонент. При его наличии окно считается открытым.
struct ImGuiOpened {};

/// @brief Сущности на которых есть компонент ImGuiDebugTool будут отобращаться в меню инстументов.
struct ImGuiDebugTool {
  std::string name; ///< наименование инструмента отображаемое в меню
  std::string category = "debug"; ///< категория (пока не реализовано)
}; 

} //namespace engine::debug

/** @}*/