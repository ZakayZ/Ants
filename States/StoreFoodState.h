//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_STATES_STOREFOODSTATE_H_
#define ANTS_STATES_STOREFOODSTATE_H_

#include "AntState.h"

class StoreFoodState : public AntState {
 public:
  StoreFoodState(SensorData& ant_senses, FoodData& ant_food,
                 PheromoneData& ant_pheromone, MovementData& ant_move, const GeneralData& ant_general)
      : AntState(ant_move, ant_general), sensor_data_(ant_senses),
        food_data_(ant_food), pheromone_data_(ant_pheromone) {}

  [[nodiscard]] uint8_t Requirements() const override { return RequireHiveStorage; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Home; }

  [[nodiscard]]  StateType GetState() const override { return StateType::HomeSearch; }

  void Decide(float delta_time) override {
    move_data_.target_direction = Normalised(sensor_data_.hive_position.value() - move_data_.position);

    if (sensor_data_.hive_storage.has_value()) {
      sensor_data_.hive_storage.value()->StoreFood(food_data_.carry_amount);
      food_data_.carry_amount = 0;
      move_data_.velocity = -move_data_.velocity;
      move_data_.target_direction = -move_data_.target_direction;
      change_state_ = StateType::FoodSearch;
    }
  }

  void Interact(WorldData& world_data, float delta_time) override {
    world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                           move_data_.position,
                                           pheromone_data_.pheromone_strength * delta_time,
                                           PheromoneType::Food);
  }

 private:
  SensorData& sensor_data_;
  FoodData& food_data_;
  PheromoneData& pheromone_data_;
};

#endif //ANTS_STATES_STOREFOODSTATE_H_
