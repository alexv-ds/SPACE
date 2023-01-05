#pragma once
#include <memory>
#include <flecs.h>
#include "opengl/GLContextLock.hpp"

namespace engine {

struct Opengl {
  Opengl(flecs::world&);
};

} //namespace engine

namespace engine::opengl {

struct OpenglContext {
  std::shared_ptr<GLContextLock> gl_lock; //Пока существует хоть один указатель на GLContextLock, opengl контекст не будет разрушен
};

} //namespace engine::opengl