//
// Created by Artem Novikov on 03.05.2023.
//

#include "World.h"

World::World(int width, int height, const std::vector<FoodSource>& food, const std::vector<std::vector<Hive>>& colony_hives)
    : food_map_(food),
      hive_map_({}),
      pheromone_map_({width, height}),
      object_map_({width, height}),
      creature_map_(),
      colonies_(),
      timer_() {

  colonies_.reserve(colony_hives.size());
  std::vector<Hive> all_hives;
  for (auto& colony : colony_hives) {
    std::vector<Hive*> colony_nests;
    colony_nests.reserve(colony.size());
    for (auto& hive : colony) {
      all_hives.emplace_back(hive);
      colony_nests.emplace_back(&all_hives.back());
    }
    colonies_.emplace_back(std::move(colony_nests));
  }
  hive_map_ = HiveMap(std::move(all_hives));
}

void World::Update() {
  timer_.Update();
  auto dt = GetDelta();

  food_map_.Update(dt);

  hive_map_.Update(dt);

  pheromone_map_.Update(dt);

  object_map_.Update(dt);

  creature_map_.Update(*this, dt);

  for (auto& colony : colonies_) {
    colony.Update(*this, dt);
  }
}
