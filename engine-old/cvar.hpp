#pragma once
#include <functional>
#include <cstdint>
#include <flecs.h>
#include <spdlog/spdlog.h>
#include "cvar/internal.hpp"
#include "engine/noncopyable.hpp"

/*
  Registered Types

  std::string
  std::int8_t
  std::uint8_t
  std::int32_t
  std::uint32_t
  std::int64_t
  std::uint64_t
  bool
  float
*/

namespace engine {

struct Cvar {
  Cvar(flecs::world&);
};

}

namespace engine::cvar {
  template <class T>
  using ChangeCb = std::function<void(flecs::entity, const T&)>;

  template <class T>
  using ValidateCb = std::function<bool(const T&)>;

  template <class T>
  class cvar_builder : public noncopyable {
  public:
    inline cvar_builder(flecs::world& world, const char* const name, T&& value)
      : world(world), name(name), default_value(std::move(value))
    {
      if (world.is_deferred()) {
        SPDLOG_WARN("World in deffered mode. Data may be lost");
      }
    }

    inline cvar_builder& on_change(ChangeCb<T>&& cb) {
      this->change_cb = std::move(cb);
      return *this;
    }
    inline cvar_builder& on_validate(ValidateCb<T>&& cb) {
      this->validate_cb = std::move(cb);
      return *this;
    }

    flecs::entity entity() {
      if (this->cvar_entity == flecs::entity::null()) {
        build_cvar();
      }
      return this->cvar_entity;
    }

    ~cvar_builder() {
      if (this->cvar_entity == flecs::entity::null()) {
        build_cvar();
      }
    }

  private:
    using DataComponent = internal::CVarDataTypeWrapper<T>;
    using UpdateCbComponent = internal::CVarUpdateCallback<T>;
    using ValidateCbComponent = internal::CVarValidateCallback<T>;
    
    flecs::world& world;
    const char* name;
    T default_value;
    ChangeCb<T> change_cb = nullptr;
    ValidateCb<T> validate_cb = nullptr;
    flecs::entity cvar_entity = flecs::entity::null();

    void build_cvar() {
      this->cvar_entity = this->world.entity(this->name);
      this->cvar_entity.set<DataComponent, internal::DataCurrent>({.value = this->default_value});
      this->cvar_entity.set<DataComponent, internal::DataDefault>({.value = this->default_value});
      SPDLOG_TRACE("CVAR CREATED: {} = {}", this->name, this->default_value);
      if (this->change_cb) {
        this->cvar_entity.set<UpdateCbComponent>({.cb = this->change_cb});
        this->change_cb(this->cvar_entity, this->default_value);
      }
      if (this->validate_cb) {
        this->cvar_entity.set<ValidateCbComponent>({.cb = this->validate_cb});
      }
    }
  };

  template <class T>
  void register_type(flecs::world& world, const char* const type_name) {
    if (!world.has<Cvar>()) {
      throw std::logic_error("Cvar Module not imported");
    }
    flecs::entity data_component = world.component<internal::CVarDataTypeWrapper<T>>(type_name);
    world.component<internal::CVarUpdateCallback<T>>("update_callback")
      .child_of(data_component);
  }

  template <class T>
  cvar_builder<T> create(flecs::world& world, const char* const name, T&& default_value) {
    if (!world.has<Cvar>()) {
      throw std::logic_error("Cvar Module not imported");
    }
    return {world, name, std::move(default_value)};
  }

  template <class T>
  void update(flecs::world& world, const char* const name, T&& value) {
    flecs::entity cvar = world.lookup(name);
    if (cvar == flecs::entity::null()) {
      SPDLOG_ERROR("Cannot update '{}' - cvar not exits", name);
      return;
    }
    //validate
    const internal::CVarValidateCallback<T>* p_validate_comp = cvar.get<internal::CVarValidateCallback<T>>();
    bool validation_result = true;
    if (p_validate_comp && p_validate_comp->cb) {
      validation_result = p_validate_comp->cb(value);
    }
    //update
    if (!validation_result) {
      SPDLOG_ERROR("Cvar validation failed. Cvar name: {}, new data: {}", name, value);
      return;
    }
    SPDLOG_TRACE("CVAR UPDATED: {} = {}", name, value); 
    if (const auto* p_change_comp = cvar.get<internal::CVarUpdateCallback<T>>(); p_change_comp && p_change_comp->cb) {
      p_change_comp->cb(cvar, value);
    }
    cvar.set<internal::CVarDataTypeWrapper<T>, internal::DataCurrent>({.value = std::move(value)});
  }

  template <class T>
  T read(flecs::world& world, const char* const name) {
    flecs::entity cvar = world.lookup(name);
    if (cvar == flecs::entity::null()) {
      const T returned_value = T();
      SPDLOG_ERROR("Cannot read '{}' - cvar not exits. Returned default constructible value: '{}'", name, returned_value);
      return returned_value;
    }
    const auto* p_data_comp = cvar.get<internal::CVarDataTypeWrapper<T>, internal::DataCurrent>();
  
    if (!p_data_comp) {
      
      const T returned_value = T();
      SPDLOG_ERROR("Cannot read '{}' data from cvar '{}' - the specified data type does not exist. "
                   "Returned default constructible value: '{}'",
                   world.entity<T>().path("::", "").c_str(), name, returned_value); 
      return returned_value;
    }
    return p_data_comp->value;
  }
}
