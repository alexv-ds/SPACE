#pragma once
#include <vector>
#include <memory>
#include <glm/vec2.hpp>
#include "flecs.h"
#include "engine/lib/noncopyable.hpp"
#include "engine/world/world-object.hpp"
#include "engine/world/transform.hpp"
#include "TreeObject.hpp"

namespace engine::world {

class SpatialSpace : public noncopyable, public std::enable_shared_from_this<SpatialSpace> {
public:
  SpatialSpace();
  ~SpatialSpace();

  /**
   * @todo избавиться от костыля
   * @param out
   * @param center
   * @param size
   * @param exclude сюда можно указать сущность, которую нужно исключить из выборки (костыль)
   */
  void query_intersects(std::vector<flecs::entity_t>& out,
                        const glm::vec2 center,
                        const glm::vec2 size,
                        const flecs::entity_t exclude = flecs::entity::null()) const;

  /**
   * @todo избавиться от костыля
   * @param out
   * @param left
   * @param top
   * @param width
   * @param height
   * @param exclude сюда можно указать сущность, которую нужно исключить из выборки (костыль)
   */
  void query_intersects(std::vector<flecs::entity_t>& out,
                        const float left,
                        const float top,
                        const float width,
                        const float height,
                        const flecs::entity_t exclude = flecs::entity::null()) const;

  [[nodiscard]] std::unique_ptr<TreeObject> create_tree_object(const flecs::entity_t entity,
                                                               const glm::vec2 center,
                                                               const glm::vec2 size);
private:
  friend class TreeObject;
  struct Impl;

  std::unique_ptr<Impl> impl;

  void update_space(TreeObject* object);
  void remove(TreeObject* object);
};


} //end of namespace engine::world