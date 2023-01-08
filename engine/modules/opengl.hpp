#pragma once
#include <memory>
#include <string>
#include <flecs.h>
#include <glad/gl.h>
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

struct GLBuffer {
  GLuint id = GL_NONE; //dsa only //glCreateBuffers
  std::shared_ptr<GLContextLock> lock;
};

struct GLShader {
  GLuint id = GL_NONE;
  std::shared_ptr<GLContextLock> lock;
};

struct VertexShader {};
struct FragmentShader {};

struct ShaderLoader {
  std::string path;
};
struct ShaderProgramLoader {
  std::string vs_path;
  std::string fs_path;
};

struct GLShaderProgram {
  GLuint id = GL_NONE;
  std::shared_ptr<GLContextLock> lock;
};

} //namespace engine::opengl