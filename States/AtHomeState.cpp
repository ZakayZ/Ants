//
// Created by Artem Novikov on 24.09.2022.
//

#include "World/WorldData.h"
#include "AtHomeState.h"

AtHomeState::AtHomeState(StateType previous_state, FoodData& ant_food, SensorData& ant_sensor,
                         PheromoneData& ant_pheromone, MovementData& ant_move, const GeneralData& ant_general)
    : AntState(ant_sensor, ant_pheromone, ant_move, ant_general),
      previous_state_(previous_state),
      food_data_(ant_food) {}

void AtHomeState::Decide(float delta_time) {
  ///  refill
  pheromone_data_.pheromone_strength = general_data_.pheromone_capacity;

  ///  came with food
  if (food_data_.carry_amount != 0) {
    sensor_data_.hive_storage.value()->StoreFood(food_data_.carry_amount);
    food_data_.carry_amount = 0;
  }

  Rotate();

  switch (general_data_.host_type) {
    case kWorker: {
      change_state_ = StateType::FoodSearch;
      break;
    }

    case kScout: {
      change_state_ = StateType::Scouting;
      break;
    }

    case kSoldier: {
      change_state_ = StateType::EnemySearch;
      break;
    }

    case kQueen: {
      change_state_ = StateType::FoodSearch;
      break;
    }
  }
}

void AtHomeState::Interact(WorldData& world_data, float delta_time) {}

