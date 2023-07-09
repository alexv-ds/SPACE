#pragma once
#include <glm/vec2.hpp>
#include <engine/world/world-object.hpp>


namespace engine::world {

struct CalculatedBBox {
  glm::vec2 center;
  glm::vec2 size;
};

CalculatedBBox calculate_bbox(const WorldObject& world);

struct CalculatedQuadTreeBBox {
  float left = 0.0f;
  float top = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
};

CalculatedQuadTreeBBox calcucalte_quad_tree_bbox(const glm::vec2 center, const glm::vec2 size);

} //end of engine::world