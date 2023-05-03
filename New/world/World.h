//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_WORLD_H_
#define ANTS_NEW_WORLD_WORLD_H_

#include "foodMap/FoodMap.h"
#include "hiveMap/HiveMap.h"
#include "pheromoneMap/PheromoneMap.h"
#include "objectMap/ObjectMap.h"
#include "creatureMap/CreatureMap.h"

class World {
 public:
  FoodMap& GetFoodMap() { return food_map_; }

  HiveMap& GetHiveMap() { return hive_map_; }

  PheromoneMap& GetPheromoneMap() { return pheromone_map_; }

  ObjectMap& GetObjectMap() { return object_map_; }

  CreatureMap& GetCreatureMap() { return creature_map_; }

 private:
  FoodMap food_map_;
  HiveMap hive_map_;
  PheromoneMap pheromone_map_;
  ObjectMap object_map_;
  CreatureMap creature_map_;
};

#endif //ANTS_NEW_WORLD_WORLD_H_
