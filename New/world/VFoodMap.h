//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_VFOODMAP_H_
#define ANTS_NEW_WORLD_VFOODMAP_H_

#include "DataTypes.h"
#include "BoundaryBox.h"

class FoodIter;

class VFoodMap {
 public:
  virtual FoodIter GetFoodList(const BoundaryBox<Float, 2>& box) = 0;

  virtual void Update(Time dt) = 0;

  virtual ~VFoodMap() = default;
};

#endif //ANTS_NEW_WORLD_VFOODMAP_H_
