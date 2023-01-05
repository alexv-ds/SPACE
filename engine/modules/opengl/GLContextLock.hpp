#pragma once
#include "../../noncopyable.hpp"

namespace engine::opengl {

//Пока держите умный поинтер на это, opengl контекст не будет разрушен
class GLContextLock : noncopyable {
public:
  virtual ~GLContextLock() = default;
};


};