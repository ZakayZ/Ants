//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_VCREATUREMAP_H_
#define ANTS_NEW_WORLD_VCREATUREMAP_H_

#include "DataTypes.h"
#include "BoundaryBox.h"

class CreatureIter;

class VCreatureMap {
 public:
  virtual CreatureIter GetCreatures(const BoundaryBox<Float, 2>& box) = 0;

  virtual void Update(Time dt) = 0;

  virtual ~VCreatureMap() = default;
};

#endif //ANTS_NEW_WORLD_VCREATUREMAP_H_
