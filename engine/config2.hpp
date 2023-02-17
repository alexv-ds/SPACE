#include <flecs.h>
#include <cstdint>
#include <functional>

#include <spdlog/spdlog.h>

namespace engine {
  struct Config2 {
    Config2(flecs::world&);
  };
};

namespace engine::config2 {
  struct Validator {
    std::function<bool(flecs::entity)> func;
  };

  class cvar : public flecs::entity {
  public:
    cvar& cvar_validate(std::function<bool(flecs::entity)>&& func);
  };

  struct ValidatedData {};
  struct UnValidatedData {};
  struct DefaultData {};
  struct ConfigVar {
    flecs::entity_t data_component = flecs::entity::null();
  };
  struct UpdateData {};

  namespace type {
    struct Int32 {
      inline Int32() noexcept = default;
      inline Int32(std::int32_t value) noexcept: value(value) {}
      std::int32_t value = 0;
    };

    struct Uint32 {
      inline Uint32() noexcept = default;
      inline Uint32(std::uint32_t value) noexcept: value(value) {}
      std::uint32_t value = 0;
    };
  } //namespace type

  template <class T>
  cvar create_var(flecs::entity e, T&& data) {
    cvar e_cvar = static_cast<cvar>(e);
    if (e_cvar.has<ConfigVar>()) {
      SPDLOG_WARN("Entity '{}' already initialised. It will be overwritten.", e_cvar.path("::", ""));
      e_cvar.remove(flecs::Wildcard, e_cvar.world().entity<UnValidatedData>());
      e_cvar.remove(flecs::Wildcard, e_cvar.world().entity<DefaultData>());
      e_cvar.remove(flecs::Wildcard, e_cvar.world().entity<ValidatedData>());
      e_cvar.remove<Validator>();
    }
    e_cvar.set<T, UnValidatedData>(data);
    e_cvar.set<T, DefaultData>(data);
    e_cvar.set<ConfigVar>({.data_component = e_cvar.world().entity<T>()});
    e_cvar.add<UpdateData>();
    return e_cvar;
  }

} //namespace engine::config2