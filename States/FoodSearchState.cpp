//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "FoodSearchState.h"

void FoodSearchState::Decide(float delta_time) {
  if (sensor_data_.food_position.has_value()) {
    change_state_ = StateType::GrabFood;
    return;
  }

  if (sensor_data_.target_ant.has_value()) {
    change_state_ = StateType::SearchAlert;
    move_data_.target_direction = -move_data_.target_direction;
    move_data_.velocity = -move_data_.velocity;
    return;
  }

  FollowPheromone(sensor_data_, delta_time);
}

void FoodSearchState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength * delta_time,
                                         PheromoneType::Home);
}

std::function<bool(Ant&)> FoodSearchState::GetProximitySensor() const {
  return [&pos = move_data_.position, sq_dist = std::pow(general_data_.visible_range, 2),
      my_idx = general_data_.colony_index](Ant& other_ant) {
    return other_ant.GetColonyIndex() != my_idx && (other_ant.GetPosition() - pos).SquaredLength() <= sq_dist;
  };
}

std::function<void(Ant&)> FoodSearchState::GetEnemySensor() const {
  return [&pos = move_data_.position, &sensor_data = sensor_data_,
      min_sq_dist = std::pow(general_data_.visible_range, 2)](Ant& other_ant) mutable {
    auto sq_dist = (other_ant.GetPosition() - pos).SquaredLength();
    if (sq_dist < min_sq_dist) {
      sensor_data.target_ant = {&other_ant};
      min_sq_dist = sq_dist;
    }
  };
}
