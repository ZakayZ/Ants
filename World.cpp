//
// Created by Artem Novikov on 27.08.2022.
//

#include "World.h"

World::World(Vector2i world_dimensions, const std::vector<FoodSource>& food,
             const std::vector<std::vector<Hive>>& hives)
    : world_data_(world_dimensions, food), ant_map_(), simulation_time_() {
  colonies_.reserve(hives.size());  /// fill queens
  ants_dividers_.reserve(colonies_.size());  /// ant inserter iterators

  for (auto& colony_hives : hives) {  /// Make world hives
    for (auto& hive : colony_hives) {
      world_data_.hive_map_.push_back(hive);
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
    ant_map_.push_back(colonies_.back().GetInitialQueen());
    ants_dividers_.push_back(--ant_map_.end());
  }
}

void World::Update() {
  simulation_time_.Update();  /// Update clock
  float delta_time = simulation_time_.GetDeltaTime();
  for (auto& ant : ant_map_) {  /// Move all ants
    ant->GetSensor().Sense(world_data_);
    ant->Interact(world_data_, delta_time);
    ant->Update(delta_time);
  }

  for (size_t i = 0; i < colonies_.size(); ++i) {  /// Create new ants and update colony info
    colonies_[i].Update(delta_time, std::insert_iterator(ant_map_, ants_dividers_[i]));
  }

  world_data_.pheromone_map_.Update(delta_time);  /// Update pheromone map
}
