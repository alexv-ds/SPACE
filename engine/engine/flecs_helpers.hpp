#pragma once
#include <string_view>
#include <flecs.h>

namespace engine {

flecs::entity lookup_by_stringview(flecs::world&, const std::string_view&);
flecs::entity entity_by_stringview(flecs::world&, const std::string_view&);

}