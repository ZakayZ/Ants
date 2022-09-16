//
// Created by Artem Novikov on 01.09.2022.
//

#ifndef ANTS_ANTDATA_WORLDDATA_H_
#define ANTS_ANTDATA_WORLDDATA_H_

#include <vector>

#include "Vector.h"
#include "PheromoneMap.h"
#include "FoodSource.h"
#include "Hive.h"

struct WorldData {
  WorldData(Vector2i world_dimensions, const std::vector<FoodSource>& food)
      : map_(world_dimensions[0], std::vector<char>(world_dimensions[1], false)),
        pheromone_map_(world_dimensions), food_map_(food), hive_map_() {

    for (int i = 0; i < world_dimensions[0]; ++i) {
      map_[i][0] = true;
      map_[i].back() = true;
    }

    for (int i = 0; i < world_dimensions[1]; ++i) {
      map_[0][i] = true;
      map_.back()[i] = true;
    }
  }

  std::vector<std::vector<char>> map_; /// TODO make class
  PheromoneMap pheromone_map_;
  std::vector<FoodSource> food_map_; /// TODO make food sources class
  std::vector<Hive> hive_map_;  /// TODO hives storage
};

#endif //ANTS_ANTDATA_WORLDDATA_H_
