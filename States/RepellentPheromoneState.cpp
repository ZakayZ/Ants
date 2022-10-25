//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "RepellentPheromoneState.h"

void RepellentPheromoneState::Interact(WorldData& world_data, float delta_time) {
  active_time_ += delta_time;
  world_data.LayPheromone(general_data_.colony_index,
                                         host_.GetPosition(),
                                         (host_.GetSensorData().pheromone_strength
                                             + host_.GetPheromoneData().pheromone_strength) * -delta_time,
                                         PheromoneType::Food);
}

void RepellentPheromoneState::Decide(float delta_time) {
  HomeSearchState::Decide(delta_time);

  if (active_time_ >= general_data_.repellent_duration) {
    host_.ChangeState<HomeSearchState>();
    return;
  }
}
