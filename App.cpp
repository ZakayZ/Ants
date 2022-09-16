//
// Created by Artem Novikov on 15.09.2022.
//

#include "App.h"
#include <vector>

int Width = 1000;
int Height = 500;

std::vector<FoodSource> food = {FoodSource(Vector2f(200, 200), 1000)};

std::vector<std::vector<Hive>> hives = {{Hive(Vector2f(125, 125))}};

App::App() : window_(sf::VideoMode(Width * kUnitLength, Height * kUnitLength), "Ants"),
             renderer_(window_, {Width, Height}),
             world_({Width, Height}, food, hives) {}

void App::Run() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window_.close();
    }

    window_.clear();
    renderer_.Render(world_);
    window_.display();

    world_.Update();
  }
}
