//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "RepellentPheromoneState.h"

void RepellentPheromoneState::Interact(WorldData& world_data, float delta_time) {
  active_time_ += delta_time;
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         -pheromone_data_.pheromone_strength * delta_time,
                                         PheromoneType::Food);
}
void RepellentPheromoneState::Decide(float delta_time) {
  HomeSearchState::Decide(delta_time);

  if (active_time_ >= general_data_.repellent_duration) {
    change_state_ = StateType::HomeSearch;
  }
}
RepellentPheromoneState::RepellentPheromoneState(SensorData& ant_senses, PheromoneData& ant_pheromone,
                                                 MovementData& ant_move, const GeneralData& ant_general)
    : HomeSearchState(ant_senses, ant_pheromone, ant_move, ant_general) {}
