#include <flecs.h>
#include <cstdint>
#include <functional>

namespace engine {
  struct Config2 {
    Config2(flecs::world&);
  };
};

namespace engine::config2 {
  struct ConfigComponent {};
  struct ValidatedData {};
  struct UnValidatedData {};

  namespace type {
    struct Int32 {
      inline Int32(std::int32_t value) noexcept: value(value) {}
      std::int32_t value;
    };

    struct Uint32 {
      inline Uint32(std::uint32_t value) noexcept: value(value) {}
      std::uint32_t value;
    };
  } //namespace type

  template <class T>
  flecs::entity create_var(flecs::world& world, const char* name, T&& data);



} //namespace engine::config2