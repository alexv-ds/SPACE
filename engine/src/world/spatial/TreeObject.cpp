#include <engine/lib/log.hpp>
#include "TreeObject.hpp"
#include "SpatialSpace.hpp"
#include "bbox_calculation.hpp"

namespace engine::world {

TreeObject::TreeObject(std::shared_ptr<SpatialSpace>&& new_space,
                       const flecs::entity_t new_entity,
                       const glm::vec2 position,
                       const glm::vec2 size)
: space(std::move(new_space)), entity(new_entity)
{
  this->update(position, size);
}

void TreeObject::update(const glm::vec2 position, const glm::vec2 size) {
  ENGINE_CRITICAL("UPDATED");
  CalculatedQuadTreeBBox tree_bbox = calcucalte_quad_tree_bbox(position, size);
  this->left = tree_bbox.left;
  this->top = tree_bbox.top;
  this->width = tree_bbox.width;
  this->height = tree_bbox.height;
  this->space->update_space(this);

  ENGINE_CRITICAL(
    "left: {}, top: {}, width: {}, height: {}",
    this->left, this->top, this->width, this->height
  );
}

TreeObject::~TreeObject() {
  ENGINE_CRITICAL("REMOVED");
  this->space->remove(this);
}

void TreeObject::query_intersects(std::vector<flecs::entity_t>& out) const {
  this->space->query_intersects(out, this->left, this->top, this->width, this->height, this->entity);
}

} //end of engine::world