#include <glad/gl.h>
#include "opengl.hpp"
#include "window.hpp"
#include "filesystem.hpp"

#include <spdlog/spdlog.h>

namespace engine::opengl::detail {

void UpdateViewport(flecs::iter it, const window::MainWindow* window, const window::event::Resized*) {
  glViewport(0, 0, window->width, window->height);
}

void PreRenderClearWindow(flecs::iter it) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void ReadShaderFile(flecs::entity e, const ShaderLoader& loader) {
  e.set<filesystem::ReadFileRequest>({
    .path = loader.path
  });
}


inline void afterload_shader_cleanup(flecs::entity& e) {
  e.remove<ShaderLoader>();
  e.remove<filesystem::ReadFileRequest>();
  e.remove<filesystem::ReadFileResponse>();
} 

void CreateShader(flecs::entity e, const ShaderLoader& loader, const filesystem::ReadFileResponse& file) {
  std::shared_ptr gl_lock = e.world().get<OpenglContext>()->gl_lock;

  GLenum shader_type;
  if (loader.path.ends_with(".fs")) {
    shader_type = GL_FRAGMENT_SHADER;
  } else if (loader.path.ends_with(".vs")) {
    shader_type = GL_VERTEX_SHADER;
  } else {
    SPDLOG_ERROR("Cannot detect shader type - '{}'", loader.path);
    afterload_shader_cleanup(e);
    return;
  }

  GLuint shader = glCreateShader(shader_type);
  const GLchar* source = reinterpret_cast<const GLchar*>(file.data.data());
  const GLint source_size[] = {static_cast<GLint>(file.data.size())};

  glShaderSource(shader, 1, &source, source_size);
  glCompileShader(shader);

  GLint success;
  GLchar info_log[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, info_log);
    SPDLOG_ERROR("Shader compilation failed - {}\n\n{}", loader.path, info_log);
    glDeleteShader(shader);
    afterload_shader_cleanup(e);
    return;
  }

  GLShader shader_component = {
    .id = shader,
    .lock = gl_lock
  };
  if (shader_type == GL_FRAGMENT_SHADER) {
    e.set<GLShader, FragmentShader>(std::move(shader_component));
  } else if (shader_type == GL_VERTEX_SHADER) {
    e.set<GLShader, VertexShader>(std::move(shader_component));
  }
  afterload_shader_cleanup(e);
}


struct ShaderProgramLoader_OnLoad {};
void ShaderProgramLoader_LoadShaders(flecs::entity e, const ShaderProgramLoader& program_loader) {  
  flecs::world world = e.world();
  e.add<ShaderProgramLoader_OnLoad>();
  world.entity()
    .set_doc_name("Frag Loader")
    .child_of(e)
    .set<ShaderLoader>({
      .path = program_loader.fs_path
    });

  world.entity()
    .set_doc_name("Vert Loader")
    .child_of(e)
    .set<ShaderLoader>({
      .path = program_loader.vs_path
    });
}

void ShaderProgramLoader_Finalyse(flecs::entity e, const GLShader& frag, const GLShader& vert) {
  std::shared_ptr gl_lock = e.world().get<OpenglContext>()->gl_lock;
  GLuint program = glCreateProgram();
  glAttachShader(program, frag.id);
  glAttachShader(program, vert.id);
  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    GLchar info_log[512];
	  glGetProgramInfoLog(program, 512, nullptr, info_log);
    SPDLOG_ERROR("Program link fail:\n\n{}", info_log);
    glDeleteProgram(program);
    e.remove<GLShader>(flecs::Wildcard);
    return;
  }
  e.remove<ShaderLoader>();
  e.remove<ShaderProgramLoader_OnLoad>();
  e.remove<GLShader>(flecs::Wildcard); 
  e.set<GLShaderProgram>({
    .id = program,
    .lock = std::move(gl_lock)
  });

}

void ShaderProgramLoader_CopyFragmentShader(flecs::entity e, GLShader& shader) {
  e.parent().set<GLShader, FragmentShader>(std::move(shader));
  shader.id = GL_NONE;
  e.destruct();
}

void ShaderProgramLoader_CopyVertexShader(flecs::entity e, GLShader& shader) {
  e.parent().set<GLShader, VertexShader>(std::move(shader));
  shader.id = GL_NONE;
  e.destruct();
}

} //namespace engine::opengl::detail

namespace engine {
using namespace opengl;


Opengl::Opengl(flecs::world& world) {
  world.import<Window>();
  world.import<Filesystem>();
  world.module<Opengl>("opengl");

  world.component<GLBuffer>();
  world.component<GLShader>();
  world.component<GLShaderProgram>();

  world.component<OpenglContext>();
  world.component<VertexShader>();
  world.component<FragmentShader>();
  world.component<ShaderLoader>();
  world.component<ShaderProgramLoader>();
  world.component<detail::ShaderProgramLoader_OnLoad>("detail::ShaderProgramLoader_OnLoad")
    .set_doc_detail("The component that indicates that ShaderProgramLoader in load state");

  //systems
  world.system("system::PreRenderClearWindow")
    .term<OpenglContext>().singleton()
    .iter(detail::PreRenderClearWindow);
  world.system<const window::MainWindow, const window::event::Resized>("system::UpdateViewport")
    .kind(flecs::PreStore)
    .term_at(1).parent()
    .iter(detail::UpdateViewport);

  world.system<const ShaderLoader>("system::ReadShaderFile")
    .multi_threaded()
    .without<filesystem::ReadFileRequest>()
    .without<filesystem::ReadFileResponse>()
    .each(detail::ReadShaderFile);
  world.system<const ShaderLoader, const filesystem::ReadFileResponse>("system::CreateShader")
    .with<OpenglContext>().singleton()
    .each(detail::CreateShader);
  
  world.system<const ShaderProgramLoader>("system::ShaderProgramLoader_LoadShaders")
    .multi_threaded()
    .without<detail::ShaderProgramLoader_OnLoad>()
    .without<GLShader>(flecs::Wildcard)
    .without<GLShaderProgram>()
    .each(detail::ShaderProgramLoader_LoadShaders);
  world.system<GLShader>("system::ShaderProgramLoader_CopyFragmentShader")
    .multi_threaded()
    .with<ShaderProgramLoader>().parent()
    .term_at(1).second<FragmentShader>()
    .each(detail::ShaderProgramLoader_CopyFragmentShader);
  world.system<GLShader>("system::ShaderProgramLoader_CopyVertexShader")
    .multi_threaded()
    .with<ShaderProgramLoader>().parent()
    .term_at(1).second<VertexShader>()
    .each(detail::ShaderProgramLoader_CopyVertexShader);
  world.system<const GLShader, const GLShader>("system::ShaderProgramLoader_Finalyse")
    .with<OpenglContext>().singleton()
    .with<ShaderProgramLoader>()
    .with<detail::ShaderProgramLoader_OnLoad>()
    .term_at(1).second<FragmentShader>()
    .term_at(2).second<VertexShader>()
    .each(detail::ShaderProgramLoader_Finalyse);   
}

} //namespace engine