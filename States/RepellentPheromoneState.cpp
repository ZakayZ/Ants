//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "RepellentPheromoneState.h"

void RepellentPheromoneState::Interact(WorldData& world_data, float delta_time) {
  active_time_ += delta_time;
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index, move_data_.position,
                                         -(sensor_data_.pheromone_strength + pheromone_data_.pheromone_strength)
                                             * delta_time,
                                         PheromoneType::Food);
}

void RepellentPheromoneState::Decide(float delta_time) {
  HomeSearchState::Decide(delta_time);

  if (active_time_ >= general_data_.repellent_duration) {
    change_state_ = StateType::HomeSearch;
  }
}
