//
// Created by Artem Novikov on 25.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_AI_H_
#define ANTS_NEW_CREATURE_AI_AI_H_

#include "DataTypes.h"

class World;

class AI {
 public:
  virtual void Decide(World& world, Time dt) = 0;

  virtual ~AI() = default;
};

#endif //ANTS_NEW_CREATURE_AI_AI_H_
