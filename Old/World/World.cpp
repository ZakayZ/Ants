//
// Created by Artem Novikov on 27.08.2022.
//

#include "World.h"
#include "Sensor.h"

World::World(Vector2i world_dimensions, const std::vector<FoodSource>& food,
             const std::vector<std::vector<Hive>>& hives)
    : colonies_(),
      ants_dividers_(),
      world_data_(world_dimensions, food, hives),
      simulation_time_() {

  colonies_.reserve(hives.size());
  ants_dividers_.reserve(colonies_.size());  /// ant inserter iterators

  for (size_t colony_index = 0; colony_index < hives.size(); ++colony_index) {
    colonies_.emplace_back(world_data_.hive_map_[colony_index], colony_index);
    world_data_.ant_map_.emplace_back(colonies_.back().GetInitialQueen());
    ants_dividers_.push_back(--world_data_.ant_map_.end());
  }
}

void World::Update() {
  /// Update clock
  simulation_time_.Update();
  float delta_time = simulation_time_.GetDeltaTime();

  /// Update Ants and map systems
  world_data_.Update(delta_time);

  /// Create new ants and update colony info
  for (size_t i = 0; i < colonies_.size(); ++i) {
    colonies_[i].Update(delta_time, std::insert_iterator(world_data_.ant_map_, ants_dividers_[i]));
  }
}
