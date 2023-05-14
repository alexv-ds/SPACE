#pragma once
#include <algorithm>

namespace engine {

template<size_t N>
struct TemlatedStringLiteral {
  constexpr TemlatedStringLiteral(const char (&str)[N]) {
    std::copy_n(str, N, value);
  }
  char value[N];
};



} //namespace engine