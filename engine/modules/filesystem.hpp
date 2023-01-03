#include <string>
#include <vector>
#include <flecs.h>


namespace engine {

struct Filesystem {
  Filesystem(flecs::world&);
};

} //namespace engine

namespace engine::filesystem {

struct ReadFileRequest {
  std::string path;
};

struct ReadFileResponse {
  std::vector<std::uint8_t> data;
};

}; //namespace engine::filesystem