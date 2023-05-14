#include <spdlog/spdlog.h>
#include <imgui-SFML.h>
#include "imgui-backend-sfml.hpp"
#include "engine/noncopyable.hpp"
#include "window-backend-sfml.hpp"
#include "window.hpp"
#include "imgui.hpp"


namespace engine::imgui_backend_sfml {

class Context::ContextLock : noncopyable {
public:
  ContextLock(std::shared_ptr<sf::RenderWindow> window): window(window) {
    SPDLOG_TRACE("Imgui context initialisation...");
    bool init_result = ImGui::SFML::Init(*window);
    assert(init_result == true);
  }

  ~ContextLock() {
    SPDLOG_TRACE("Imgui context destroy...");
    ImGui::SFML::Shutdown(*this->window);
  }

private:
  std::shared_ptr<sf::RenderWindow> window;
};

Context::Context() = default;
Context::~Context() = default;


static void ContextInit(flecs::iter it, const window_backend_sfml::MainWindowSFML_RenderWindow* window_data) {
  assert(window_data->window != nullptr);
  flecs::world world = it.world();

  Context imgui_context;
  imgui_context.lock = std::make_shared<Context::ContextLock>(window_data->window);

  world.set<Context>(imgui_context);
  world.add<imgui::ImguiContext>();
} 

static void HandleEvents(flecs::iter it, const window::MainWindow* window_data, const Context*) {
  //SPDLOG_INFO("BOP");
  //for (a)
}


} //namespace engine::imgui_backend_sfml




engine::ImguiBackendSfml::ImguiBackendSfml(flecs::world& world) {
  using namespace imgui_backend_sfml;

  world.import<Window>();
  world.import<WindowBackendSfml>();
  world.module<ImguiBackendSfml>("imgui_backend_sfml");
  
  world.component<Context>();

  world.system<const window_backend_sfml::MainWindowSFML_RenderWindow>("system::InitContext")
    .arg(1).singleton()
    .without<Context>().singleton()
    .iter(ContextInit);

  assert(world.get<Window>() != nullptr);
  world.system<const window::MainWindow, const Context>("system::HandleEvents")
    .kind(world.get<Window>()->load_events_phase)
    .arg(1).singleton()
    .arg(2).singleton()
    .iter(HandleEvents);
}