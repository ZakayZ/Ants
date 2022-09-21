//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_STATES_HOMESEARCHSTATE_H_
#define ANTS_STATES_HOMESEARCHSTATE_H_

#include "AntState.h"

class HomeSearchState : public AntState {
 public:
  HomeSearchState(
      SensorData& ant_senses, PheromoneData& ant_pheromone, MovementData& ant_move, const GeneralData& ant_general)
      : AntState(ant_move, ant_general), sensor_data_(ant_senses), pheromone_data_(ant_pheromone) {}

  [[nodiscard]] uint8_t Requirements() const override { return RequireHome | RequirePheromone; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Home; }

  [[nodiscard]]  StateType GetState() const override { return StateType::HomeSearch; }

  void Decide(float delta_time) override {
    if (sensor_data_.hive_position.has_value()) {
      change_state_ = StateType::StoreFood;
      return;
    }

    if (sensor_data_.pheromone_strength > 0.01f) {
      move_data_.target_direction =
          Normalised(move_data_.target_direction + (delta_time * sensor_data_.pheromone_strength)
              * (sensor_data_.pheromone_center - move_data_.position));
    }
  }

  void Interact(WorldData& world_data, float delta_time) override {
    world_data.pheromone_map_.LayPheromone(move_data_.position, pheromone_data_.pheromone_strength * delta_time,
                                           general_data_.colony_index, PheromoneType::Food);
  }

 protected:
  SensorData& sensor_data_;
  PheromoneData& pheromone_data_;
};

#endif //ANTS_STATES_HOMESEARCHSTATE_H_
