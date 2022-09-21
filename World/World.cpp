//
// Created by Artem Novikov on 27.08.2022.
//

#include "World.h"

World::World(Vector2i world_dimensions, const std::vector<FoodSource>& food,
             const std::vector<std::vector<Hive>>& hives)
    : colonies_(),
      ants_dividers_(),
      world_data_(world_dimensions, food, hives.size()),
      ant_map_(BoundaryBox2f({0.f, 0.f}, {float(world_dimensions[0]), float(world_dimensions[1])}), {50, 50}),
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
    ant_map_.emplace_back(colonies_.back().GetInitialQueen());
    ants_dividers_.push_back(--ant_map_.end());
  }
}

void World::Update() {
  /// Update clock
  simulation_time_.Update();
  float delta_time = simulation_time_.GetDeltaTime();

  /// Move all ants
  for (auto& ant : ant_map_) {
    ant.object->GetSensor().Sense(world_data_);
    ant.object->Interact(world_data_, delta_time);
    ant.object->Update(delta_time);
  }
  ant_map_.UpdatePositions();


  /// Create new ants and update colony info
  for (size_t i = 0; i < colonies_.size(); ++i) {
    colonies_[i].Update(delta_time, std::insert_iterator(ant_map_, ants_dividers_[i]));
  }

  /// Update pheromone map
  world_data_.pheromone_map_.Update(delta_time);

  /// Update hives
  world_data_.hive_map_.Update(delta_time);

  /// Update food sources
  world_data_.food_map_.Update(delta_time);
}
