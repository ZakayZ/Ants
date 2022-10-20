//
// Created by Artem Novikov on 23.09.2022.
//

#include "World/WorldData.h"
#include "AlertColonyState.h"

void AlertColonyState::Decide(float delta_time) {
  if (host_.GetSensorData().hive_position.has_value()) {
    FollowPoint(host_.GetSensorData().hive_position.value());

    if (host_.GetSensorData().hive_storage.has_value()) {
      Rotate();
      host_.AlertColony();
      host_.ChangeState<AtHomeState>();
    }
  } else {
    FollowPheromone(delta_time);
  }
}

void AlertColonyState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         host_.GetPosition(),
                                         host_.GetPheromoneData().pheromone_strength * delta_time,
                                         PheromoneType::Enemy);
}
