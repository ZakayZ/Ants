//
// Created by Artem Novikov on 23.09.2022.
//

#include "World/WorldData.h"
#include "AlertColonyState.h"

AlertColonyState::AlertColonyState(SensorData& ant_senses, PheromoneData& ant_pheromone,
                                   MovementData& ant_move, const GeneralData& ant_general)
    : AntState(ant_move, ant_general), sensor_data_(ant_senses), pheromone_data_(ant_pheromone) {}

void AlertColonyState::Decide(float delta_time) {
  FollowPoint(sensor_data_.hive_position.value());

  if (sensor_data_.hive_storage.has_value()) {
    sensor_data_.hive_storage.value()->Alert(pheromone_data_.pheromone_strength);
    change_state_ = StateType::FoodSearch;
    Rotate();
  }
}

void AlertColonyState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength * delta_time,
                                         PheromoneType::Enemy);
}
