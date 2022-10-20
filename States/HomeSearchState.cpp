//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "HomeSearchState.h"
#include "Ants/Ant.h"
#include "World/Sensor.h"

void HomeSearchState::Decide(float delta_time) {
  if (host_.GetSensorData().hive_position.has_value()) {
    if (host_.GetSensorData().hive_storage.has_value()) {
      host_.ChangeState<AtHomeState>();
      return;
    }

    FollowPoint(host_.GetSensorData().hive_position.value());
  } else {
    FollowPheromone(delta_time);
  }
}

void HomeSearchState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         host_.GetPosition(),
                                         host_.GetPheromoneData().pheromone_strength * delta_time,
                                         PheromoneType::Food);
}
