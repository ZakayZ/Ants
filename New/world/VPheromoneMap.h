//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_VPHEROMONEMAP_H_
#define ANTS_NEW_WORLD_VPHEROMONEMAP_H_

#include "DataTypes.h"
#include "BoundaryBox.h"

class PheromoneIter;

struct PheromoneData {
  Float total_strength;
  Position mean_position;
};

class VPheromoneMap {
 public:
  virtual PheromoneIter GetPheromone(const BoundaryBox<Float, 2>& box) = 0;

  virtual PheromoneData GetPheromoneStrength(const BoundaryBox<Float, 2>& box) = 0;

  virtual void Update(Time dt) = 0;

  virtual ~VPheromoneMap() = default;
};

#endif //ANTS_NEW_WORLD_VPHEROMONEMAP_H_
