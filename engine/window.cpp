#include <type_traits>
#include <spdlog/spdlog.h>
#include "window.hpp"

namespace engine::window::detail {

static void CleanupEventStorage(flecs::iter it, MainWindow* window) {
  window->events.clear();
}

static void ExitOnClosed(flecs::iter it, MainWindow* window) {
  window->events.iterate([world = it.world()](const window::Event& event) {
    if (event.is<window::event::Closed>()) {
      SPDLOG_TRACE("Get close event");
      world.quit();
    }
  });
}

static void HandleExitButton(flecs::iter it, MainWindow* window, const ExitButton* exit_button) {
  if (exit_button->key == Key::Unknown && exit_button->scancode == Scancode::Unknown) {
    return;
  }
  window->events.iterate([world = it.world(), exit_button](Event& event) {
    if (!event.is<event::KeyPressed>()) {
      return;
    } 
    const event::KeyPressed& event_data = event.get<event::KeyPressed>();
    if (event_data.key != Key::Unknown && event_data.key == exit_button->key) {
      using KeyUnderlying = std::underlying_type_t<decltype(event_data.key)>;
      SPDLOG_TRACE("Close button pressed. Keycode: {}", static_cast<KeyUnderlying>(event_data.key));
      event.discard();
      world.quit();
      return;
    }
    if (event_data.scancode != Scancode::Unknown && event_data.scancode == exit_button->scancode) {
      using ScancodeUnderlying = std::underlying_type_t<decltype(event_data.scancode)>;
      SPDLOG_TRACE("Close button pressed. Scancode: {}", static_cast<ScancodeUnderlying>(event_data.scancode));
      event.discard();
      world.quit();
      return;
    }
  });
}

static void UpdateSize(flecs::iter it, MainWindow* window) {
  window->events.iterate([window](const Event& event) {
    if (event.is<event::Resized>()) {
      const auto& resize_event = event.get<event::Resized>();
      window->height = resize_event.height;
      window->width = resize_event.width;
    }
  });
}

}; //namespace engine::window::private


namespace engine {
  using namespace window;

  Window::Window(flecs::world& world) {
    world.import<flecs::units>();
    world.module<Window>("window");

    //reflection
    static_assert(std::is_same_v<std::underlying_type_t<Style>, std::uint32_t>);
    world.component<Style>("reflection::Style")
      //.bit("None", static_cast<std::uint32_t>(Style::None))
      .bit("Titlebar", static_cast<std::uint32_t>(Style::Titlebar))
      .bit("Resize", static_cast<std::uint32_t>(Style::Resize))
      .bit("Close", static_cast<std::uint32_t>(Style::Close))
      .bit("Fullscreen", static_cast<std::uint32_t>(Style::Fullscreen));
      //.bit("Default", static_cast<std::uint32_t>(Style::Default));

    //components
    world.component<MainWindowInit>();
    world.component<MainWindow>();
    world.component<ExitOnClosed>();
    world.component<ExitButton>();

    //phases
    this->load_events_phase = world.entity("phase::load_events")
      .add(flecs::Phase)
      .depends_on(flecs::OnLoad);
    
    flecs::entity post_load_events_phase = world.entity("detail::phase::post_load_events")
      .add(flecs::Phase)
      .depends_on(this->load_events_phase);
  

    //systems
    world.system<MainWindow>("system::CleanupEventStorage")
      .kind(flecs::PostFrame)
      .arg(1).singleton()
      .iter(detail::CleanupEventStorage);

    world.system<MainWindow>("system::UpdateSize")
      .kind(post_load_events_phase)
      .arg(1).singleton()
      .iter(detail::UpdateSize);
    
    world.system<MainWindow>("system::ExitOnClosed")
      .kind(post_load_events_phase)
      .arg(1).singleton()
      .with<ExitOnClosed>().singleton()
      .iter(detail::ExitOnClosed);

    world.system<MainWindow, const ExitButton>("system::HandleExitButton")
      .kind(post_load_events_phase)
      .arg(1).singleton()
      .arg(2).singleton()
      .iter(detail::HandleExitButton);
  };
}


