#include <flecs.h>
#include <cstdint>
#include <functional>

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
    inline cvar(flecs::entity e): e(e) {}

    template<class DataType>
    config_var& cvar_validate(std::function<bool(const DataType& value)>&& func) {
      std::function<bool(flecs::entity)> validator = [typed_validator = std::move(func)](flecs::entity e) {
        
      }
      //e.set<Validator>({.func = std::move(func)});
    }

  private:
    flecs::entity e;
  };

  struct ValidatedData {};
  struct UnValidatedData {};
  struct DefaultData {};
  struct ConfigVar {
    flecs::entity_t data_component = flecs::entity::null();
  };

  namespace type {
    struct Int32 {
      inline Int32() = default;
      inline Int32(std::int32_t value) noexcept: value(value) {}
      std::int32_t value = 0;
    };

    struct Uint32 {
      inline Uint32() = default;
      inline Uint32(std::uint32_t value) noexcept: value(value) {}
      std::uint32_t value = 0;
    };
  } //namespace type

  template <class T>
  flecs::entity create_var(flecs::entity e_cvar, T&& data) {
    e_cvar.set<T, UnValidatedData>(data);
    e_cvar.set<T, DefaultData>(data);
    e_cvar.set<ConfigVar>({.data_component = e_cvar.world().entity<T>()});
    return e_cvar;
  }

} //namespace engine::config2