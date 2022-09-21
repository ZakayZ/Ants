//
// Created by Artem Novikov on 27.08.2022.
//

#include "World.h"
#include "Sensor.h"

World::World(Vector2i world_dimensions, const std::vector<FoodSource>& food,
             const std::vector<std::vector<Hive>>& hives)
    : colonies_(),
      ants_dividers_(),
      world_data_(world_dimensions, food, hives.size()),
      simulation_time_() {
  colonies_.reserve(hives.size());  /// fill queens
  ants_dividers_.reserve(colonies_.size());  /// ant inserter iterators

  for (auto& colony_hives : hives) {  /// Make world hives
    for (auto& hive : colony_hives) {
      world_data_.hive_map_.AddHive(hive);
    }
  }

  size_t current_index = 0;
  for (const auto& hive : hives) {  /// wire world hives to colonies and dividers to colonies
    auto colony_hives = std::vector<Hive*>();
    for (size_t j = 0; j < hive.size(); ++j) {
      colony_hives.push_back(&world_data_.hive_map_[current_index]);
      ++current_index;
    }

    colonies_.emplace_back(colony_hives);
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
