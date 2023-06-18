//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_WORLD_H_
#define ANTS_NEW_WORLD_WORLD_H_

#include <vector>

#include "foodMap/FoodMap.h"
#include "hiveMap/HiveMap.h"
#include "pheromoneMap/PheromoneMap.h"
#include "objectMap/ObjectMap.h"
#include "creatureMap/CreatureMap.h"

#include "colony/Colony.h"

#include "utils/Timer.h"

class World {
 public:
  using ColonyMap = std::vector<Colony>;

  World(int width, int height, const std::vector<FoodSource>& food, const std::vector<std::vector<Hive>>& colony_hives);

  FoodMap& GetFoodMap() { return food_map_; }

  HiveMap& GetHiveMap() { return hive_map_; }

  PheromoneMap& GetPheromoneMap() { return pheromone_map_; }

  ObjectMap& GetObjectMap() { return object_map_; }

  CreatureMap& GetCreatureMap() { return creature_map_; }

  ColonyMap& GetColonyMap() { return colonies_; }

  [[nodiscard]] const FoodMap& GetFoodMap() const { return food_map_; }

  [[nodiscard]] const HiveMap& GetHiveMap() const { return hive_map_; }

  [[nodiscard]] const PheromoneMap& GetPheromoneMap() const { return pheromone_map_; }

  [[nodiscard]] const ObjectMap& GetObjectMap() const { return object_map_; }

  [[nodiscard]] const CreatureMap& GetCreatureMap() const { return creature_map_; }

  [[nodiscard]] const ColonyMap& GetColonyMap() const { return colonies_; }

  void Update();

  [[nodiscard]] Float GetDelta() const { return timer_.GetDeltaTime(); }

  [[nodiscard]] Float GetTime() const { return timer_.GetElapsedTime(); }

 private:
  FoodMap food_map_;
  HiveMap hive_map_;
  PheromoneMap pheromone_map_;
  ObjectMap object_map_;
  CreatureMap creature_map_;

  ColonyMap colonies_;

  Timer timer_;
};

#endif //ANTS_NEW_WORLD_WORLD_H_
