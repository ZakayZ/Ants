//
// Created by Artem Novikov on 01.09.2022.
//

#ifndef ANTS_ANTDATA_WORLDDATA_H_
#define ANTS_ANTDATA_WORLDDATA_H_

#include <vector>

#include "Vector.h"
#include "Collections/SpatialHashing.h"

#include "Ants/Ant.h"
#include "Map.h"
#include "FoodMap.h"
#include "HiveMap.h"

struct WorldData {
 public:
  using AntHandler = SpatialHashing<std::unique_ptr<Ant>, float, 2>;

  WorldData(Vector2i world_dimensions,
            const std::vector<FoodSource>& food,
            const std::vector<std::vector<Hive>>& hives);

  [[nodiscard]] float GetPheromone(size_t colony_index, const Vector2f& position, PheromoneType type) const {
    return map_.GetPheromone(colony_index, position, type);
  }

  [[nodiscard]] auto GetPheromoneCenter(
      size_t colony_index, const Vector2f& position, float side_length, PheromoneType type) const {
    return map_.GetPheromoneCenter(colony_index, position, side_length, type);
  }

  void LayPheromone(size_t colony_index, const Vector2f& position, float added_pheromone, PheromoneType type) {
    map_.LayPheromone(colony_index, position, added_pheromone, type);
  }

  void Update(float delta_time);

  Map map_;
  FoodMap food_map_;
  HiveMap hive_map_;
  AntHandler ant_map_;
};

#endif //ANTS_ANTDATA_WORLDDATA_H_
