#pragma once
#include <memory>
#include <flecs.h>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace engine {
  struct WindowBackendSfml {
    WindowBackendSfml(flecs::world&);

    //internal data
    float suspicious_size_msg_delay = 0; 
  };
}

namespace engine::window_backend_sfml {
  struct MainWindowSFML {
    std::shared_ptr<sf::WindowBase> window;
  };
  
  struct MainWindowSFML_RenderWindow {
    std::shared_ptr<sf::RenderWindow> window;
  };
}