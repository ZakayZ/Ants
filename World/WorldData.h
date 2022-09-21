//
// Created by Artem Novikov on 01.09.2022.
//

#ifndef ANTS_ANTDATA_WORLDDATA_H_
#define ANTS_ANTDATA_WORLDDATA_H_

#include <vector>

#include "Vector.h"
#include "Collections/SpatialHashing.h"

#include "Ants/Ant.h"
#include "TileMap.h"
#include "PheromoneMap.h"
#include "FoodMap.h"
#include "HiveMap.h"

class WorldData {
 public:
  using AntHandler = SpatialHashing<std::unique_ptr<Ant>, float, 2>;

  WorldData(Vector2i world_dimensions, const std::vector<FoodSource>& food, size_t colonies_number);

  void Update(float delta_time);

  TileMap map_;
  PheromoneMap pheromone_map_;
  FoodMap food_map_;
  HiveMap hive_map_;
  AntHandler ant_map_;
};

#endif //ANTS_ANTDATA_WORLDDATA_H_
