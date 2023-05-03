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
  FoodMap& FoodMap() { return food_map_; }

  HiveMap& HiveMap() { return hive_map_; }

  PheromoneMap& PheromoneMap() { return pheromone_map_; }

  ObjectMap& ObjectMap() { return object_map_; }

  CreatureMap& CreatureMap() { return creature_map_; }

 private:
  FoodMap food_map_;
  HiveMap hive_map_;
  PheromoneMap pheromone_map_;
  ObjectMap object_map_;
  CreatureMap creature_map_;
};

#endif //ANTS_NEW_WORLD_WORLD_H_
