//
// Created by Artem Novikov on 18.06.2023.
//

#include <vector>

#include "App.h"

int Width = 300;
int Height = 300;


std::vector<FoodSource> food =
    {FoodSource(Vector2f(150, 150), 10, 2)};

std::vector<std::vector<Hive>> hives = {{Hive(Vector2f(100, 100), 1000, 3)}};/*, {Hive(Vector2f(200, 200), 100)}};*/

App::App() : renderer_(Width, Height),
             world_(Width, Height, food, hives) {}

void App::Run() {
  while (renderer_.Display(world_)) {
    world_.Update();
  }
}