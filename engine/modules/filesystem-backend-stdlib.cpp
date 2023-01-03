#include <fstream>
#include <cstdint>
#include <spdlog/spdlog.h>
#include "filesystem-backend-stdlib.hpp"
#include "filesystem.hpp"


namespace engine::filesystem_backend_stdlib::detail {

void ReadFile(flecs::entity e, const filesystem::ReadFileRequest& req) {
  SPDLOG_TRACE("Reading file: {}", req.path);
  try {
    std::ifstream file(req.path, std::ios::in | std::ios::binary | std::ios::ate);
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<std::uint8_t> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);

    e.set<filesystem::ReadFileResponse>({
      .data=std::move(buffer)
    });
  }
  catch(const std::exception& exception) {
    SPDLOG_ERROR("Cannot read '{}' - {}", req.path, exception.what());
  }
  
}

} //namespace engine::filesystem_backend_stdlib::detail

namespace engine {
using namespace engine::filesystem_backend_stdlib;


FilesystemBackendStdlib::FilesystemBackendStdlib(flecs::world& world) {
  world.import<Filesystem>();
  world.module<FilesystemBackendStdlib>("filesystem_backend_stdlib");

  world.system<const filesystem::ReadFileRequest>()
    .multi_threaded()
    //.term<filesystem::ReadFileResponse>().out()
    .without<filesystem::ReadFileResponse>()
    .each(detail::ReadFile);

}

} //namespace engine
