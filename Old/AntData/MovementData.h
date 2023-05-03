//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_ANTDATA_MOVEMENTDATA_H_
#define ANTS_ANTDATA_MOVEMENTDATA_H_

#include "Vector.h"

struct MovementData {
  explicit MovementData(const Vector2f& position) : position(position) {}
  Vector2f position;
  Vector2f velocity{};
  Vector2f target_direction{};
  float random_cooldown{};
};

#endif //ANTS_ANTDATA_MOVEMENTDATA_H_
