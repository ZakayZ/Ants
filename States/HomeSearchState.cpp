//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "HomeSearchState.h"

void HomeSearchState::Decide(float delta_time) {
  if (sensor_data_.hive_position.has_value()) {
    if (sensor_data_.hive_storage.has_value()) {
      change_state_ = StateType::Idle;
      return;
    }

    FollowPoint(sensor_data_.hive_position.value());
  } else {
    FollowPheromone(delta_time);
  }
}

void HomeSearchState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength * delta_time,
                                         PheromoneType::Food);
}
