#include "window.hpp"

//#include "window/Event.hpp"

namespace engine::window::detail {

void CleanupEventStorage(flecs::iter it, MainWindow* window) {
  window->events.clear();
}

/*
void UpdateSize(flecs::iter it, const window::EventOld*, const window::event::Resized* resized) {
  const window::event::Resized* last_event = resized + (*it.end() - 1);
  MainWindow* window = it.world().get_mut<MainWindow>();
  window->height = last_event->height;
  window->width = last_event->width;
}

int compare_event_index(flecs::entity_t e1, const window::EventOld* event1, flecs::entity_t e2, const window::EventOld* event2) {
  return (event1->index > event2->index) - (event1->index < event2->index);
}
*/
}; //namespace engine::window::detail


namespace engine {
  using namespace window;

  Window::Window(flecs::world& world) {
    world.import<flecs::units>();
    world.module<Window>("window");

    static_assert(std::is_same_v<std::underlying_type_t<Style>, std::uint32_t>);
    world.component<Style>("Style")
      .bit("None", static_cast<std::uint32_t>(Style::None))
      .bit("Titlebar", static_cast<std::uint32_t>(Style::Titlebar))
      .bit("Resize", static_cast<std::uint32_t>(Style::Resize))
      .bit("Close", static_cast<std::uint32_t>(Style::Close))
      .bit("Fullscreen", static_cast<std::uint32_t>(Style::Fullscreen))
      .bit("Default", static_cast<std::uint32_t>(Style::Default));

    world.component<MainWindowInit>();
    world.component<MainWindow>();

    //systems
    world.system<MainWindow>("system::CleanupEventStorage")
      .kind(flecs::PreUpdate)
      .arg(1).singleton()
      .iter(detail::CleanupEventStorage);

  };
}


