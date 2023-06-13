#pragma once
#include <memory>
#include <flecs.h>

namespace engine {

/// @brief Создает мир и импортирует модули движка
std::shared_ptr<flecs::world> create_world(int argc, char* argv[]);
std::shared_ptr<flecs::world> create_world();

/**
 * @brief Шаг обновления мира.
 * Cм. ecs_progress() в flecs piplene.h
 * 
 * @param world мир созданный с помощью create_world()
 * @param dt время прошедшее с прошлого кадра (0 что бы подсчитать автоматически)
 * @return true мир не требует завершения
 * @return false мир завершается - можно разрывать цикл
 */
bool update_world(flecs::world& world, const float dt = 0);

inline bool update_world(const std::shared_ptr<flecs::world>& world, const float dt = 0) {
  return update_world(*world, dt);
}

/**
 * @brief Singleton компонент, если установлен, то доступено управление окном sokol app.
 */
struct SokolAppContext {};

struct SokolGfxContext {};
  
} //namespace engine



