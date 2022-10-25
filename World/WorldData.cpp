//
// Created by Artem Novikov on 22.09.2022.
//

#include "WorldData.h"
#include "Sensor.h"

WorldData::WorldData(
    Vector2i world_dimensions, const std::vector<FoodSource>& food, const std::vector<std::vector<Hive>>& hives)
    : map_(hives.size(), world_dimensions),
      food_map_(food),
      hive_map_(hives),
      ant_map_(BoundaryBox2f({0.f, 0.f}, {float(world_dimensions[0]), float(world_dimensions[1])}), {20, 20}) {}

void WorldData::Update(float delta_time) {
  /// Move all ants
  for (auto it = ant_map_.begin(); it != ant_map_.end(); ++it) {
    auto& ant = *it->object;
    ant.GetSensor().Sense(*this);
    ant.Interact(*this, delta_time);
    ant.Update(delta_time);
    if (!ant.IsAlive()) {
      ant_map_.erase(it--);
    }
  }
  ant_map_.UpdatePositions();

  /// Update pheromone map
  map_.Update(delta_time);

  /// Update hives
  hive_map_.Update(delta_time);

  /// Update food sources
  food_map_.Update(delta_time);
}
