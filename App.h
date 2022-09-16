//
// Created by Artem Novikov on 15.09.2022.
//

#ifndef ANTS__APP_H_
#define ANTS__APP_H_

#include <SFML/Graphics.hpp>

#include "World.h"
#include "Renderer.h"

class App {
 public:
  App();

  void Run();

  ~App() = default;
 private:
  sf::RenderWindow window_;
  Renderer renderer_;
  World world_;
};

#endif //ANTS__APP_H_
