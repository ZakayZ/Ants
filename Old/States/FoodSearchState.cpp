//
// Created by Artem Novikov on 22.09.2022.
//

#include "World/WorldData.h"
#include "FoodSearchState.h"

void FoodSearchState::Decide(float delta_time) {
  if (host_.GetSensorData().food_position.has_value()) {
    FollowPoint(host_.GetSensorData().food_position.value());

    if (host_.GetSensorData().food_source.has_value()
        || (host_.GetSensorData().food_position.value() -host_.GetPosition()).SquaredLength()
            <= std::pow(general_data_.ant_size, 2)) {
      Rotate();
      host_.ResetPheromone();

      if (host_.GetSensorData().food_source.has_value()) {
        host_.TakeFood();
        host_.ChangeState<HomeSearchState>();
        return;
      }
      host_.ChangeState<RepellentPheromoneState>();
    }
  } else {
    FollowPheromone(delta_time);
  }
}

void FoodSearchState::Interact(WorldData& world_data, float delta_time) {
  world_data.LayPheromone(general_data_.colony_index,
                                         host_.GetPosition(),
                                         host_.GetPheromoneData().pheromone_strength * delta_time,
                                         PheromoneType::Home);
}
