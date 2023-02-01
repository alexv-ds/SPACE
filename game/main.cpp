#include <format>
#include <spdlog/spdlog.h>
#include <flecs.h>
#include "../engine/engine/setup_spdlog.hpp"
#include "atmospherics.hpp"


struct Hydrogen {};
struct Oxygen {};
struct Nitrogen {};

//using namespace game;

int main() {
  engine::setup_spdlog();
  flecs::world world;
  world.set_threads(4);
  world.set_target_fps(60);
  world.import<flecs::monitor>();
  world.import<game::Atmospherics>();

  world.component<Nitrogen>("gases::Nitrogen")
    .set<game::atmospherics::SpecificHeat>({
      .value = 20
    });
    
  

  

  flecs::entity mixture = world.entity("mixture")
    .set<game::atmospherics::GasMixture>({
      .volume = 2.5f,
      .energy = 609810
    })
    .set<game::atmospherics::GasData, Nitrogen>({
      .amount = 183.41f
    });
     

  world.app().enable_rest().run();
}