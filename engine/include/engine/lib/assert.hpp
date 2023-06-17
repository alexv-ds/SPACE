#pragma once
#include <cassert>

//TODO: Избавиться от assert(), использовать аналог из flecs
//assert() плох тем, что он не срабатывает в релизной сборке
#define ENGINE_ASSERT(expr) assert(expr)