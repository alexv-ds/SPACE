#include <variant>
#include <spdlog/spdlog.h>
#include "engine/flecs_helpers.hpp"
#include "config.hpp"

using namespace std::string_view_literals;

namespace engine::config {
  namespace detail {
    struct UnitialisedVar {
      VariantType data;
    };

    static void OnSet_Var(flecs::entity e) {
      e.add<Changed>();
    }

    static void ExecuteUpdateCallbacks(flecs::iter it, const Var* vars, const ChangeListener* listeners) {
      flecs::world world = it.world();
      for (auto i : it) {
        if (!listeners[i].cb) {
          SPDLOG_ERROR("Cannot execute update callback. ChangeListener has null callback. Listener Entity: {}", 
                       it.entity(i).path("::", ""));
          continue;
        }
        listeners[i].cb(world, vars[i].data);
      }
    }

    static void PostFrameCleanup(flecs::iter it) {
      it.world().remove_all<Changed>();
    }

  void print_error_report(const std::string_view expected_type,
                          const VariantType& variant,
                          const std::string_view var_name,
                          const std::string_view listener_name,
                          flecs::world& world)
  {
    SPDLOG_ERROR("Cannot handle onchange cvar callback. "
                 "Expected '{}' value type, but geted '{}'. "
                 "Var Entity: '{}', Listener Entity: '{}'",
                 expected_type,
                 stored_typename(variant),
                 entity_by_stringview(world, var_name).path("::", ""),
                 entity_by_stringview(world, listener_name).path("::", ""));
  }

  } //namespace detail;

  std::string_view stored_typename(const VariantType& data) noexcept {
    if (std::holds_alternative<std::string>(data)) {
      return "string"sv;
    } else if (std::holds_alternative<std::int32_t>(data)) {
      return "int32"sv;
    } else if (std::holds_alternative<float>(data)) {
      return "float"sv;
    } else {
      return "UNKNOWN TYPE. IMPLEMENT ME!"sv;
    }
  }
  
  void create_var(flecs::world& world, const std::string_view name, VariantType&& data) {
    flecs::entity entity = entity_by_stringview(world, name);

    if (entity.has<Var>()) {
      SPDLOG_WARN("Double initialization of a config variable. Config Entity: {}", entity.path("::", ""));
    }

    //Проверим наличие UnitialisedVar, если оно есть
    //А быть оно может в случае когда функцию update_var() вызвали раньше чем create_var()
    //Это нормально, но в таком случае нужно проверить тип UnitialisedVar на соответствие
    //типу, который был присвоен при вызове create_var()
    if (detail::UnitialisedVar* uninitialised_var = entity.get_ref<detail::UnitialisedVar>().get(); uninitialised_var) {
      //check stored type
      if (uninitialised_var->data.index() == data.index()) {
        data = std::move(uninitialised_var->data);
      } else {
        SPDLOG_WARN("Config Entity ({}) has a UnitialisedVar ({}), but its type is different from Var ({})."
                    " UnitialisedVar ignored.",
                     entity.path("::", ""), stored_typename(uninitialised_var->data), stored_typename(data));
      }
      entity.remove<detail::UnitialisedVar>();
    }
    entity.set<Var>({.data = std::move(data)});
  }

  void update_var(flecs::world& world, const std::string_view name, VariantType&& data) {
    flecs::entity entity = entity_by_stringview(world, name);

    //Если на сущности есть Var, то значит она была инициализирована
    //и компонент UnitialisedVar не используется
    if (Var* var = entity.get_ref<Var>().get(); var) {
      //Проверяем хранящиеся типы, сделать это можно по индексам

      if (data.index() == var->data.index()) {
        //Так же проверяем на равенство, нам незачем делать пустую работу
        //если оно и так равно
        if (var->data != data) {
          var->data = std::move(data);
          entity.add<Changed>();
        }
      } else {
        SPDLOG_WARN("Cannot set '{}' data to '{}' variable. Config Entity: {}",
                    stored_typename(data), stored_typename(var->data), entity.path("::", ""));
      }
    } else {
      entity.set<detail::UnitialisedVar>({.data = std::move(data)});
    }
  }

  void create_var_listener(flecs::world& world,
                          const std::string_view var_name,
                          const std::string_view listener_name,
                          ChangeListener::CbType&& onchange_cb)
  {
    flecs::entity var_entity = entity_by_stringview(world, var_name);
    flecs::entity listener_entity = entity_by_stringview(world, listener_name);
    
    if (listener_entity.has<ChangeListener>()) {
      SPDLOG_WARN("Listener double initialization. Listener Entity: {}. Var entity: {}.",
                  listener_entity.path("::", ""), var_entity.path("::", ""));
    }
    if (const Var* var = var_entity.get<Var>(); var && !var_entity.has<Changed>()) {
      onchange_cb(world, var->data);
    }

    //Если Сущность представляющая переменную и слушатель является одной сущностью
    //то вешаем на нее не отношение, а непосредственно компонентн
    //Потому что не может быть отношений на саму себя из-за флага flecs::Traversable
    //у ChangeListener
    if (var_entity.id() == listener_entity.id()) {
      listener_entity.set<ChangeListener>({.cb = std::move(onchange_cb)});
    } else {
      listener_entity.set<ChangeListener>(var_entity, {.cb = std::move(onchange_cb)});
    }
  }

  const VariantType* get_var(flecs::world& world, const std::string_view name) {
    static thread_local std::string str_buff;
    flecs::entity entity = lookup_by_stringview(world, name);
    if (entity == flecs::entity::null()) {
      return nullptr;
    }
    if (const Var* var = entity.get<Var>(); var) {
      return &(var->data);
    }
    return nullptr;
  }
} //namespace engine::config

engine::Config::Config(flecs::world& world) {
  using namespace config;
  world.module<Config>("config");

  //components
  world.component<Var>();
  world.component<Changed>();
  world.component<ChangeListener>()
    .add(flecs::Traversable);
  world.component<detail::UnitialisedVar>("detail::UnitialisedVar");
  
  //observers
  {
    flecs::entity observers_scope = world.entity("observer");
    world.observer()
      .with<Var>()
      .event(flecs::OnSet)
      .each(detail::OnSet_Var)
      .child_of(observers_scope)
      .set_name("OnSet_Var");    
  }

  //systems
  world.system<const Var, const ChangeListener>("system::ExecuteUpdateCallbacks")
    .kind(flecs::PostFrame)
    .arg(1).up<ChangeListener>()
    .arg(2).second(flecs::Wildcard)
    .with<Changed>().up<ChangeListener>()
    .iter(detail::ExecuteUpdateCallbacks);
  
  world.system<const Var, const ChangeListener>("system::ExecuteUpdateCallback_SelfListeners")
    .kind(flecs::PostFrame)
    .with<Changed>()
    .iter(detail::ExecuteUpdateCallbacks);

  world.system("system::PostFrameCleanup")
    .kind(flecs::PostFrame)
    .iter(detail::PostFrameCleanup);  
}

