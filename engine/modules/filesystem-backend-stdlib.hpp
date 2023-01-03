#include <flecs.h>

namespace engine {

struct FilesystemBackendStdlib {
  FilesystemBackendStdlib(flecs::world&);
};

} //namespace engine