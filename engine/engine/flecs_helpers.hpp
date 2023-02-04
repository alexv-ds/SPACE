#pragma once
#include <string_view>
#include <flecs.h>

namespace engine {

flecs::entity entity_by_stringview(flecs::world&, const std::string_view&);

}