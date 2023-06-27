#pragma once
#include <cmath>
#include <glm/mat3x3.hpp>
#include <glm/vec2.hpp>

namespace engine {

//TODO: Не работает :(
inline void mat3_decompose(const glm::mat3& mat,
                           glm::vec2& translation,
                           glm::vec2& scale,
                           float& angle)
{
  translation = mat[2];
  scale.x = mat[0][0];
  scale.y = mat[1][1];
  angle = std::acos(mat[0][0]);
}


} //end of namespace engine