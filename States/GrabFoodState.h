//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_STATES_GRABFOODSTATE_H_
#define ANTS_STATES_GRABFOODSTATE_H_

#include "AntState.h"

class GrabFoodState : public AntState {
 public:
  GrabFoodState(SensorData& ant_senses, MovementData& ant_move, FoodData& ant_food,
                PheromoneData& ant_pheromone, const GeneralData& ant_general)
      : sensor_data_(ant_senses), move_data_(ant_move),
        food_data_(ant_food), pheromone_data_(ant_pheromone), general_data_(ant_general) {}

  [[nodiscard]] uint8_t Requirements() const override { return RequireFoodStorage; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Home; }

  [[nodiscard]]  StateType GetState() const override { return StateType::HomeSearch; }

  void Decide() override {
    move_data_.target_direction = Normalised(sensor_data_.food_position.value() - move_data_.position);

    if (sensor_data_.food_source.has_value()) {
      food_data_.carry_amount =
          sensor_data_.food_source.value()->GetFood(general_data_.max_capacity - food_data_.carry_amount);
      move_data_.velocity = -move_data_.velocity;
      move_data_.target_direction = -move_data_.target_direction;
      change_state_ = StateType::HomeSearch;
    } else {
      /// TODO make pheromone cleanup state
    }
  }

  void Interact(WorldData& world_data, float delta_time) override { /// TODO reduce
    world_data.pheromone_map_.LayPheromone(move_data_.position, pheromone_data_.pheromone_strength * delta_time,
                                           PheromoneType::Home);
  }

 private:
  SensorData& sensor_data_;
  MovementData& move_data_;
  FoodData& food_data_;
  PheromoneData& pheromone_data_;
  const GeneralData& general_data_;
};

#endif //ANTS_STATES_GRABFOODSTATE_H_
