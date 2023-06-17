//
// Created by Artem Novikov on 09.05.2023.
//

#ifndef ANTS_NEW_CREATURE_MOVEDATA_H_
#define ANTS_NEW_CREATURE_MOVEDATA_H_

#include "DataTypes.h"

struct MoveData {
  Position position;
  Velocity velocity;
  Vector2<Float> target_direction;
};

#endif //ANTS_NEW_CREATURE_MOVEDATA_H_
