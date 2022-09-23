//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "StoreFoodState.h"

StoreFoodState::StoreFoodState(SensorData& ant_senses, FoodData& ant_food, PheromoneData& ant_pheromone,
                               MovementData& ant_move, const GeneralData& ant_general)
    : AntState(ant_move, ant_general), sensor_data_(ant_senses), food_data_(ant_food), pheromone_data_(ant_pheromone) {}

void StoreFoodState::Decide(float delta_time) {
  FollowPoint(sensor_data_.hive_position.value());

  if (sensor_data_.hive_storage.has_value()) {
    sensor_data_.hive_storage.value()->StoreFood(food_data_.carry_amount);
    food_data_.carry_amount = 0;
    move_data_.velocity = -move_data_.velocity;
    move_data_.target_direction = -move_data_.target_direction;
    change_state_ = StateType::FoodSearch;
  }
}

void StoreFoodState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength * delta_time,
                                         PheromoneType::Food);
}
