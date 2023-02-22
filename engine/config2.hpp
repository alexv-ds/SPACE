#include <flecs.h>
#include <cstdint>
#include <functional>
#include <format>

#include "engine/FlecsScopeGuard.hpp"

#include <spdlog/spdlog.h>

namespace engine::config2::type {
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
} //namespace engine::config2::type

template <>
struct std::formatter<engine::config2::type::Int32> : std::formatter<std::string> {
  auto format(engine::config2::type::Int32& data, format_context& ctx) {
    return formatter<string>::format(
      std::format("{}", data.value), ctx);
  }
};

namespace engine {
  struct Config2 {
    flecs::entity validate_phase = flecs::entity::null();
    flecs::entity update_phase = flecs::entity::null();
    flecs::entity notify_phase = flecs::entity::null();

    Config2(flecs::world&);
  };
};

namespace engine::config2 {

  struct SystemsInitialised {};
  struct ValidatedData {};
  struct UnValidatedData {};
  struct DefaultData {};
  struct ConfigVar {
    flecs::entity_t data_component = flecs::entity::null();
  };
  struct UpdateData {};
  struct OnUpdate {};

  struct Validator {
    std::function<bool(flecs::entity)> func;
  };

  class cvar : public flecs::entity {
  public:
    cvar& cvar_validate(std::function<bool(flecs::entity)>&& func);

    template <class T>
    cvar& cvar_validate(std::function<bool(flecs::entity, const T&)>&& func) {
      cvar_validate([typed_func = std::move(func)](flecs::entity e) -> bool {
        const T* p_data = e.get<T, UnValidatedData>();
        if (!p_data) {
          SPDLOG_ERROR("Cvar validation fail: has no {} component", e.world().entity<T>().path("::", ""));
          return false;
        }
        return typed_func(e, *p_data);
      });
      return *this;
    }

    template <class T>
    cvar& cvar_validate(std::function<bool(const T&)>&& func) {
      cvar_validate([typed_func = std::move(func)](flecs::entity e) -> bool {
        const T* p_data = e.get<T, UnValidatedData>();
        if (!p_data) {
          SPDLOG_ERROR("Cvar validation fail: has no {} component", e.world().entity<T>().path("::", ""));
          return false;
        }
        return typed_func(*p_data);
      });
      return *this;
    }
  };
  struct ToLogString {
    std::function<std::string(flecs::entity)> to_string;
  };

  namespace detail {
    template <class T>
    void create_systems_for_type(flecs::world& world) {
      if (world.entity<T>().has<SystemsInitialised>()) {
        return;
      }
      const Config2* config = world.get<Config2>();
      if (!config) {
        SPDLOG_ERROR("Config Module is not loaded");
        return;
      }
      world.entity<T>().add<SystemsInitialised>();
      FlecsScopeGuard scope_guard(world.entity<Config2>());
      world.system<T>(std::format("system::Update_{}", world.entity<T>().path("_", "")).c_str())
        .kind(config->update_phase)
        .arg(1).second<UnValidatedData>()
        .each([](flecs::entity e, T& data) {
          e.set<T, ValidatedData>(std::move(data));
          e.remove<T, UnValidatedData>();
          SPDLOG_TRACE("CVAR: {} = {} ({})", e.path("::", ""), data, e.world().entity<T>().path("::", ""));
        });
      world.system<T, const T, const Validator>(std::format("system::Validate_{}", world.entity<T>().path("_", "")).c_str())
        .kind(config->validate_phase)
        .arg(1).second<UnValidatedData>()
        .arg(2).second<DefaultData>()
        .each([](flecs::entity e, T& unvalidated_data, const T& default_data, const Validator& validator) {
          if (!validator.func(e)) {
            unvalidated_data = default_data;
          }
        });
    }
  } //namespace detail

  template <class T>
  cvar create_var(flecs::entity e, T&& data) {
    {
      flecs::world world = e.world();
      detail::create_systems_for_type<T>(world);
    }
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

  template <class T>
  void update_cvar(flecs::entity e, T&& data) {
    e.set<T, UnValidatedData>(std::move(data));
  }

  template <class T>
  void update_cvar(flecs::world& world, const char* entity_name, T&& data) {
    update_cvar(world.entity(entity_name), std::move(data));
  }

} //namespace engine::config2