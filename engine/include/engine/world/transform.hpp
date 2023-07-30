#pragma once
#include <glm/mat3x3.hpp>

namespace engine::world {


/**
 * При добавлении этого компонента, будет так же добавлено отношение (Scale,Global)
 * Где Scale - локальный увеличение, (Scale, Global) - глобальное
 *
 */
struct Scale {
  float x = 1.0f;
  float y = 1.0f;
};

/**
 * @see Scale
 */
struct Rotation {
  float angle = 0.0f; //radians
};

/**
 * @see Scale
 */
struct Position {
  float x = 0.0f;
  float y = 0.0f;
};

struct Transform {
  glm::mat3 matrix = glm::mat3(1.0f);
};

struct Global {};

} //end of namespace engine::world