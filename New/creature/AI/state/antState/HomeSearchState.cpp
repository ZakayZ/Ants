//
// Created by Artem Novikov on 25.05.2023.
//

#include "HomeSearchState.h"

#include "creature/ant/Ant.h"
#include "world/World.h"

void HomeSearchState::Decide(World& world, Time dt) {
  host_.LayPheromone(dt);
  FollowPheromone(world, PheromoneType::Home, dt);

  if (hive_ != nullptr) {
    FollowPoint(hive_->GetPosition());
    if (hive_->IsClose(host_.GetPosition())) {
      host_.GetStateManager().HiveDecision(*hive_);
    }
  } else {
    FindHive(world);
  }
}

void HomeSearchState::FindHive(World& world) {
  auto& map = world.GetObjectMap();
  for (auto& hive : world.GetHiveMap().GetHiveList(host_.VisibleRange())) {
    if ((host_.GetPosition() - hive.GetPosition()).SquaredLength() <= std::pow(general_data_.visible_range, 2)
        && map.Visible(host_.GetPosition(), hive.GetPosition())) {
      hive_ = &hive;
      break;
    }
  }
}
