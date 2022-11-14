//
// Created by Artem Novikov on 14.11.2022.
//

#include "World/WorldData.h"
#include "LayingState.h"
#include "Utils/RandomGenerator.h"

const float LayingState::ResetTime = 1.f;

void LayingState::Decide(float delta_time) {
  if (!host_.GetSensorData().hive_position.has_value()) {
    host_.ChangeState<HomeSearchState>();
    return;
  }

  reposition_cooldown_ += delta_time;
  if (reposition_cooldown_ >= ResetTime) {
    reposition_cooldown_ -= ResetTime;
    patrol_position_ = host_.GetSensorData().hive_position.value()
        + 0.5f * RandomGenerator().GetVector2f() * general_data_.visible_range;
  }
  FollowPoint(patrol_position_);
}

void LayingState::Interact(WorldData& world_data, float delta_time) {}
