//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "GrabFoodState.h"

GrabFoodState::GrabFoodState(SensorData& ant_senses, FoodData& ant_food, PheromoneData& ant_pheromone,
                             MovementData& ant_move, const GeneralData& ant_general)
    : AntState(ant_move, ant_general), sensor_data_(ant_senses), food_data_(ant_food), pheromone_data_(ant_pheromone) {}

void GrabFoodState::Decide(float delta_time) {
  FollowPoint(sensor_data_.food_position.value());

  if (sensor_data_.food_source.has_value()
      || (sensor_data_.food_position.value() - move_data_.position).SquaredLength()
          < std::pow(general_data_.ant_size, 2)) {
    Rotate();
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

void GrabFoodState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength * delta_time,
                                         PheromoneType::Home);
}
