#pragma once
#include <memory>
#include <type_traits>
#include <cstring>
#include "engine/world/world-object.hpp"
#include "TreeObject.hpp"
#include "bbox_calculation.hpp"


#include <engine/lib/log.hpp>

namespace engine::world {

//component
class SpatialInternal {
public:
  inline SpatialInternal(const WorldObject& new_cache, std::unique_ptr<TreeObject>&& new_tree_object)
    : object_cache(new_cache), tree_object(std::move(new_tree_object))
  {};

  /**
   * @param new_cache
   * @return были ли изменения
   */
  inline bool update(const WorldObject& new_cache) {
    static_assert(std::is_standard_layout_v<WorldObject>);
    if (new_cache != this->object_cache) {
      this->object_cache = new_cache;
      auto [center, size] = calculate_bbox(object_cache);
      this->tree_object->update(center, size);
      return true;
    }
    return false;
  }

  inline const TreeObject& get_tree_object() {
    return *tree_object;
  }

private:
  WorldObject object_cache;
  std::unique_ptr<TreeObject> tree_object;
};


} //end of engine::world