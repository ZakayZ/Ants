//
// Created by Artem Novikov on 15.09.2022.
//

#include "App.h"
#include <vector>

int Width = 300;
int Height = 300;

std::vector<FoodSource> food =
    {FoodSource(Vector2f(150, 150), 10)};

std::vector<std::vector<Hive>> hives = {{Hive(Vector2f(100, 100), 10000)}};/*, {Hive(Vector2f(200, 200), 100)}};*/

App::App() : window_(sf::VideoMode(Width * Renderer::UnitLength, Height * Renderer::UnitLength), "Ants"),
             renderer_(window_, {Width, Height}),
             world_({Width, Height}, food, hives) {}

void App::Run() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }
    }

    window_.clear();
    renderer_.Render(world_);
    window_.display();

    world_.Update();
  }
}
