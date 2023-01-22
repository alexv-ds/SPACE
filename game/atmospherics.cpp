#include "spdlog/spdlog.h"
#include "atmospherics.hpp"

namespace game::atmospherics::detail {

void PreUpdateCleanup(flecs::iter it, GasMixture* mixture) {
  for (auto i : it) {
    mixture[i].specific_heat = 0;
    mixture[i].amount = 0;
  }
}

void UpdateAmount(flecs::iter it, GasMixture* mixture, const GasData* data) {
  for (auto i : it) {
    mixture[i].amount += data[i].amount;
  }
}

void UpdateSpecificHeat(flecs::iter it, GasMixture* mixture, const GasData* data) {
  const SpecificHeat* specific_heat = it.pair(2).second().get<SpecificHeat>();
  if (!specific_heat) {
    SPDLOG_ERROR("Relation has no SpecificHeat component: {}", it.str());
    return;
  }
  for (auto i : it) {
    if (mixture[i].amount > 0) {
      mixture[i].specific_heat += (data[i].amount / mixture[i].amount) * specific_heat->value;
    }
  }
}

constexpr float R_GAS_CONSTANT = 8.31446261815324f;

void UpdateTempAndPressure(flecs::iter it, GasMixture* mixture) {
  for (auto i : it) {
    //temperature
    float mult_heat_with_amount = mixture[i].amount * mixture[i].specific_heat;
    if (mult_heat_with_amount > 0) {
      mixture[i].temperature = mixture[i].energy / mult_heat_with_amount;
    } else {
      mixture[i].temperature = 0;
    }

    //pressure
    if (mixture[i].volume > 0) {
      mixture[i].pressure = (mixture[i].amount * R_GAS_CONSTANT * mixture[i].temperature) / mixture[i].volume;
    } else {
      mixture[i].pressure = 0;
    }
    
  }
}

} //namespace game::atmospherics::detail

namespace game {
using namespace atmospherics;

Atmospherics::Atmospherics(flecs::world& world) {
  world.module<Atmospherics>("atmospherics");

  //components
  world.component<GasMixture>()
    .member<decltype(GasMixture::volume)>("volume")
    .member<decltype(GasMixture::energy)>("energy")
    .member<decltype(GasMixture::temperature)>("temperature")
    .member<decltype(GasMixture::pressure)>("pressure")
    .member<decltype(GasMixture::specific_heat)>("specific_heat")
    .member<decltype(GasMixture::amount)>("amount");
  
  world.component<SpecificHeat>()
    .member<decltype(SpecificHeat::value)>("value");

  world.component<GasData>()
    .member<decltype(GasData::amount)>("amount")
    .add(flecs::Acyclic);

  //systems
  world.system<GasMixture>("system::PreUpdateCleanup")
    .iter(detail::PreUpdateCleanup);

  world.system<GasMixture, const GasData>("system::UpdateAmount")
    .arg(2).second(flecs::Wildcard)
    .iter(detail::UpdateAmount);
  
  world.system<GasMixture, const GasData>("system::UpdateSpecificHeat")
    .arg(2).second(flecs::Wildcard)
    .iter(detail::UpdateSpecificHeat);

  world.system<GasMixture>("system::UpdateTempAndPressure")
    .iter(detail::UpdateTempAndPressure);
}

} //namespace game
