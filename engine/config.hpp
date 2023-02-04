#pragma once
#include <string>
#include <string_view>
#include <functional>
#include <variant>
#include <flecs.h>

namespace engine {

struct Config {
  Config(flecs::world&);
};

} //namespace engine

namespace engine::config {
  //добавим в тип варианта для того, что бы meta модуль flecs не считал 
  //за один тип наш VariantType и такой же std::varint<string, int32, float>
  namespace detail { struct VariantUniqueTag {};}

//При добавлении нового типа соответствующе обновить stored_typename()

using VariantType = std::variant<std::string, std::int32_t, float, detail::VariantUniqueTag>;
std::string_view stored_typename(const VariantType& data) noexcept;

struct Var {
  VariantType data;
};

struct Changed {};
struct ChangeListener {
  using CbType = std::function<void(flecs::world&, const VariantType&)>;
  CbType cb;
};

void create_var_listener(flecs::world& world,
                         const std::string_view var_name,
                         const std::string_view listener_name,
                         ChangeListener::CbType&& onchange_cb);

void create_var(flecs::world& world, const std::string_view name, VariantType&& data);
void update_var(flecs::world& world, const std::string_view name, VariantType&& data);
//return nullptr if var not exits
const VariantType* get_var(flecs::world& world, const std::string_view name);

} //namespace engine::config