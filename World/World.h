//
// Created by Artem Novikov on 27.08.2022.
//

#ifndef ANTS__WORLD_H_
#define ANTS__WORLD_H_

#include <vector>
#include <chrono>
#include "Vector.h"
#include "Collections/SpatialHashing.h"

#include "Colony.h"
#include "WorldData.h"
#include "Utils/Timer.h"

class World {
 public:
  using AntHandler = std::list<std::unique_ptr<Ant>>;
  World(Vector2i world_dimensions, const std::vector<FoodSource>& food, const std::vector<std::vector<Hive>>& hives);

  [[nodiscard]] const WorldData& GetWorldData() const { return world_data_; }

  [[nodiscard]] const auto& GetColonies() const { return colonies_; }

  [[nodiscard]] const auto& GetAnts() const { return ant_map_; }

  [[nodiscard]] const auto& GetTimer() const { return simulation_time_; }

  void Update();

 private:
  std::vector<Colony> colonies_;
  std::vector<AntHandler::iterator> ants_dividers_;

  WorldData world_data_;
  AntHandler ant_map_;
  Timer simulation_time_;
};

#endif //ANTS__WORLD_H_
