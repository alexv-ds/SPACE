#include <cmath>
#include "bbox_calculation.hpp"

namespace engine::world {

CalculatedBBox calculate_bbox(const WorldObject& object) {
  CalculatedBBox bbox;

  bbox.center.x = object.global_position.x;
  bbox.center.y = object.global_position.y;

  bbox.size.x = std::abs(object.size_x * object.global_scale.x);
  bbox.size.y = std::abs(object.size_y * object.global_scale.y);

  return bbox;
}

CalculatedQuadTreeBBox calcucalte_quad_tree_bbox(const glm::vec2 center, const glm::vec2 size) {
  return {
    .left = center.x - size.x / 2.0f,
    .top = center.y - size.y / 2.0f,
    .width = size.x,
    .height = size.y
  };
}

} //end of namespace engine::world