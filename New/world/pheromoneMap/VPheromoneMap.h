//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_VPHEROMONEMAP_H_
#define ANTS_NEW_WORLD_VPHEROMONEMAP_H_

#include "DataTypes.h"
#include "BoundaryBox.h"
#include "PheromoneType.h"

class PheromoneList;

struct PheromoneData {
  Float total_strength;
  Position mean_position;
};

class VPheromoneMap {
 public:
  virtual PheromoneList GetPheromone(const BoundaryBox<Float, 2>& box, PheromoneType type) = 0;

  virtual void AddPheromone(const Vector<Float, 2>& position, Float strength, PheromoneType type) = 0;

  virtual PheromoneData GetPheromoneStrength(const BoundaryBox<Float, 2>& box, PheromoneType type) = 0;

  virtual void Update(Time dt) = 0;

  virtual ~VPheromoneMap() = default;
};

#endif //ANTS_NEW_WORLD_VPHEROMONEMAP_H_
