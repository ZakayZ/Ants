//
// Created by Artem Novikov on 22.09.2022.
//

#include "WorldData.h"
#include "Sensor.h"

WorldData::WorldData(
    Vector2i world_dimensions, const std::vector<FoodSource>& food, const std::vector<std::vector<Hive>>& hives)
    : map_(world_dimensions),
      pheromone_map_(hives.size(), world_dimensions),
      food_map_(food),
      hive_map_(hives),
      ant_map_(BoundaryBox2f({0.f, 0.f}, {float(world_dimensions[0]), float(world_dimensions[1])}), {50, 50}) {}

void WorldData::Update(float delta_time) {
  /// Move all ants
  for (auto& ant : ant_map_) {
    ant.object->GetSensor().Sense(*this);
    ant.object->Interact(*this, delta_time);
    ant.object->Update(delta_time);
  }
  ant_map_.UpdatePositions();

  /// Update pheromone map
  pheromone_map_.Update(delta_time);

  /// Update hives
  hive_map_.Update(delta_time);

  /// Update food sources
  food_map_.Update(delta_time);
}
