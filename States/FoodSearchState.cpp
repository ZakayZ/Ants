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

  if (sensor_data_.pheromone_strength > 0.01f) {
    move_data_.target_direction =
        Normalised(move_data_.target_direction + (delta_time * sensor_data_.pheromone_strength)
            * (sensor_data_.pheromone_center - move_data_.position));
  }
}

void FoodSearchState::Interact(WorldData& world_data, float delta_time)  {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength * delta_time,
                                         PheromoneType::Home);
}
