//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_STATES_FOODSEARCHSTATE_H_
#define ANTS_STATES_FOODSEARCHSTATE_H_

#include "AntState.h"

class FoodSearchState : public AntState {
 public:
  FoodSearchState(SensorData& ant_senses, MovementData& ant_move, PheromoneData& ant_pheromone)
      : sensor_data_(ant_senses), move_data_(ant_move),
        pheromone_data_(ant_pheromone) {}

  [[nodiscard]] uint8_t Requirements() const override { return RequireFood | RequirePheromone; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Food; }

  [[nodiscard]]  StateType GetState() const override { return StateType::FoodSearch; }

  void Decide() override {
    if (sensor_data_.food_position.has_value()) {
      move_data_.target_direction = Normalised(sensor_data_.food_position.value() - move_data_.position);
      change_state_ = StateType::GrabFood;
      return;
    }

    if (sensor_data_.pheromone_strength > 0.01f) {
      move_data_.target_direction = Normalised(move_data_.target_direction + sensor_data_.pheromone_strength
          * (sensor_data_.pheromone_center - move_data_.position));  /// TODO add delta time
    }
  }

  void Interact(WorldData& world_data, float delta_time) override {
    world_data.pheromone_map_.LayPheromone(move_data_.position, pheromone_data_.pheromone_strength * delta_time,
                                           PheromoneType::Home);
  }

 private:
  SensorData& sensor_data_;
  MovementData& move_data_;
  PheromoneData& pheromone_data_;
};

#endif //ANTS_STATES_FOODSEARCHSTATE_H_
