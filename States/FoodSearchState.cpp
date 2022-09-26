//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "FoodSearchState.h"

FoodSearchState::FoodSearchState(FoodData& ant_food, SensorData& ant_sensor, PheromoneData& ant_pheromone,
                                 MovementData& ant_move, const GeneralData& ant_general)
    : AntState(ant_sensor, ant_pheromone, ant_move, ant_general), food_data_(ant_food) {}

void FoodSearchState::Decide(float delta_time) {
  if (sensor_data_.food_position.has_value()) {
    FollowPoint(sensor_data_.food_position.value());

    if (sensor_data_.food_source.has_value()
        || (sensor_data_.food_position.value() - move_data_.position).SquaredLength()
            <= std::pow(general_data_.ant_size, 2)) {
      Rotate();
      pheromone_data_.pheromone_strength = general_data_.pheromone_capacity;
      change_state_ = StateType::RepellentPheromone;

      if (sensor_data_.food_source.has_value()) {
        food_data_.carry_amount = sensor_data_.food_source.value()->GetFood(
            general_data_.max_capacity - food_data_.carry_amount);
        change_state_ = StateType::HomeSearch;
      }
    }
  } else {
    FollowPheromone(delta_time);
  }
}

void FoodSearchState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength * delta_time,
                                         PheromoneType::Home);
}
