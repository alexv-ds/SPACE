#pragma once
#include <functional>

namespace engine::cvar::internal {

template <class T>
struct CVarDataTypeWrapper {
  T value;
};

template <class T>
struct CVarUpdateCallback {
  std::function<void(flecs::entity, const T&)> cb;
};

struct DataDefault {};
struct DataCurrent {};
struct NotifyCallbacks {};

struct DataNew {};
struct DataValidated {};




}