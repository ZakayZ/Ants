//
// Created by Artem Novikov on 01.09.2022.
//

#ifndef ANTS_ANTDATA_WORLDDATA_H_
#define ANTS_ANTDATA_WORLDDATA_H_

#include <vector>

#include "Vector.h"
#include "TileMap.h"
#include "PheromoneMap.h"
#include "FoodMap.h"
#include "HiveMap.h"

struct WorldData {
  WorldData(Vector2i world_dimensions, const std::vector<FoodSource>& food, size_t colonies_number)
      : map_(world_dimensions), pheromone_map_(world_dimensions, colonies_number), food_map_(food), hive_map_({}) {}

  TileMap map_;
  PheromoneMap pheromone_map_;
  FoodMap food_map_;
  HiveMap hive_map_;
};

#endif //ANTS_ANTDATA_WORLDDATA_H_
