//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_STATES_GRABFOODSTATE_H_
#define ANTS_STATES_GRABFOODSTATE_H_

#include "AntState.h"

class GrabFoodState : public AntState {
 public:
  GrabFoodState(SensorData& ant_senses, FoodData& ant_food,
                PheromoneData& ant_pheromone, MovementData& ant_move, const GeneralData& ant_general)
      : AntState(ant_move, ant_general), sensor_data_(ant_senses),
        food_data_(ant_food), pheromone_data_(ant_pheromone) {}

  [[nodiscard]] uint8_t Requirements() const override { return RequireFoodStorage; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Home; }

  [[nodiscard]]  StateType GetState() const override { return StateType::HomeSearch; }

  void Decide(float delta_time) override {
    move_data_.target_direction = Normalised(sensor_data_.food_position.value() - move_data_.position);

    if (sensor_data_.food_source.has_value()
        || (sensor_data_.food_position.value() - move_data_.position).SquaredLength()
            < std::pow(general_data_.ant_size, 2)) {
      move_data_.velocity = -move_data_.velocity;
      move_data_.target_direction = -move_data_.target_direction;
      change_state_ = StateType::RepellentPheromone;
      if (sensor_data_.food_source.has_value()) {
        food_data_.carry_amount =
            sensor_data_.food_source.value()->GetFood(general_data_.max_capacity - food_data_.carry_amount);
        change_state_ =
            food_data_.carry_amount < general_data_.max_capacity ? StateType::RepellentPheromone
                                                                 : StateType::HomeSearch;
      }
    }
  }

  void Interact(WorldData& world_data, float delta_time) override {
    world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                           move_data_.position,
                                           pheromone_data_.pheromone_strength * delta_time,
                                           PheromoneType::Home);
  }

 private:
  SensorData& sensor_data_;
  FoodData& food_data_;
  PheromoneData& pheromone_data_;
};

#endif //ANTS_STATES_GRABFOODSTATE_H_
