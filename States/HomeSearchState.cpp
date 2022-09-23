//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "HomeSearchState.h"

HomeSearchState::HomeSearchState(SensorData& ant_senses, PheromoneData& ant_pheromone,
                                 MovementData& ant_move, const GeneralData& ant_general)
    : AntState(ant_move, ant_general), sensor_data_(ant_senses), pheromone_data_(ant_pheromone) {}

void HomeSearchState::Decide(float delta_time) {
  if (sensor_data_.hive_position.has_value()) {
    change_state_ = StateType::StoreFood;
    return;
  }

  FollowPheromone(sensor_data_, delta_time);
}

void HomeSearchState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength * delta_time,
                                         PheromoneType::Food);
}