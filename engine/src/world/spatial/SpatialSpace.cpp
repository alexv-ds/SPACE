#include "SpatialSpace.hpp"
#include "LooseQuadtree.h"
#include "bbox_calculation.hpp"

namespace engine::world {

struct BoundingBoxExtractor {
  inline static void ExtractBoundingBox(const TreeObject* in, loose_quadtree::BoundingBox<float>* out) {
    out->left = in->left;
    out->top = in->top;
    out->width = in->width;
    out->height = in->height;
  }
};

struct SpatialSpace::Impl : noncopyable {
  using LoseeQuadTreeType = loose_quadtree::LooseQuadtree<float, TreeObject, BoundingBoxExtractor>;
  LoseeQuadTreeType quad_tree;
};

SpatialSpace::SpatialSpace() : impl(std::make_unique<Impl>()) {
};
SpatialSpace::~SpatialSpace() = default;

std::unique_ptr<TreeObject> SpatialSpace::create_tree_object(const flecs::entity_t entity,
                                                             const glm::vec2 center,
                                                             const glm::vec2 size) {
  return std::make_unique<TreeObject>(shared_from_this(), entity, center, size);
}

void SpatialSpace::update_space(TreeObject* object) {
  this->impl->quad_tree.Update(object);
}

void SpatialSpace::remove(TreeObject* object) {
  this->impl->quad_tree.Remove(object);
}

void SpatialSpace::query_intersects(std::vector<flecs::entity_t>& out,
                                    const glm::vec2 center,
                                    const glm::vec2 size,
                                    const flecs::entity_t exclude) const
{
  const CalculatedQuadTreeBBox bbox = calcucalte_quad_tree_bbox(center, size);
  this->query_intersects(out, bbox.left, bbox.top, bbox.width, bbox.height, exclude);
}

void SpatialSpace::query_intersects(std::vector<flecs::entity_t>& out,
                                    const float left,
                                    const float top,
                                    const float width,
                                    const float height,
                                    const flecs::entity_t exclude) const
{
  Impl::LoseeQuadTreeType::Query query = this->impl->quad_tree.QueryIntersectsRegion({left, top, width, height});
  while(!query.EndOfQuery()) {
    const flecs::entity_t entity = query.GetCurrent()->get_entity();
    if (entity != exclude) {
      out.push_back(entity);
    }
    query.Next();
  }
}

} //end of namespace engine::world