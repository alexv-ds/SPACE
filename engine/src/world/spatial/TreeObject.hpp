#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>
#include <flecs.h>
#include <engine/lib/noncopyable.hpp>
#include <engine/world/world-object.hpp>

namespace engine::world {

class SpatialSpace;

class TreeObject : public noncopyable {
public:
  /**
   * @param new_space
   * @param position центр объекта
   * @param size размеры
   */
  TreeObject(std::shared_ptr<SpatialSpace>&& new_space,
             const flecs::entity_t new_entity,
             const glm::vec2 position,
             const glm::vec2 size);
  ~TreeObject();

  /**
   * @param position центр объекта
   * @param size размеры
   */
  void update(const glm::vec2 position, const glm::vec2 size);

  void query_intersects(std::vector<flecs::entity_t>& out) const;

  inline flecs::entity_t get_entity() {
    return this->entity;
  }

private:
  friend struct BoundingBoxExtractor;

  const flecs::entity_t entity;
  const std::shared_ptr<SpatialSpace> space;
  float left = 0.0f;
  float top = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
};

} //end of engine::world