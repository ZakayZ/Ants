//
// Created by Artem Novikov on 23.09.2022.
//

#include "World/WorldData.h"
#include "AlertColonyState.h"

void AlertColonyState::Decide(float delta_time) {
  if (sensor_data_.hive_position.has_value()) {
    FollowPoint(sensor_data_.hive_position.value());

    if (sensor_data_.hive_storage.has_value()) {
      Rotate();
      sensor_data_.hive_storage.value()->Alert(pheromone_data_.pheromone_strength);
      change_state_ = StateType::Idle;
    }
  } else {
    FollowPheromone(delta_time);
  }
}

void AlertColonyState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength * delta_time,
                                         PheromoneType::Enemy);
}
