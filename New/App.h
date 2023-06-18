//
// Created by Artem Novikov on 18.06.2023.
//

#ifndef ANTS_NEW_APP_H_
#define ANTS_NEW_APP_H_

#include "world/World.h"
#include "render/Renderer.h"

class App {
 public:
  App();

  void Run();

 private:
  Renderer renderer_;
  World world_;
};

#endif //ANTS_NEW_APP_H_
