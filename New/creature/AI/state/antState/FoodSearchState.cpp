//
// Created by Artem Novikov on 09.05.2023.
//

#include "FoodSearchState.h"

#include "creature/ant/Ant.h"
#include "world/World.h"

#include "WorkerAI.h"

void FoodSearchState::Decide(World& world, Time dt) {
  host_.LayPheromone(dt);
  FollowPheromone(world, PheromoneType::Food, dt);

  if (food_ != nullptr) {
    FollowPoint(food_->GetPosition());
    if (food_->IsClose(host_.GetPosition())) {
      static_cast<WorkerAI&>(host_.GetStateManager()).ResourceDecision(*food_);
    }
  } else {
    FindFood(world);
  }
}

void FoodSearchState::FindFood(World& world) {
  auto& map = world.GetObjectMap();
  for (auto& food : world.GetFoodMap().GetFoodList(host_.VisibleRange())) {
    if ((host_.GetPosition() - food.GetPosition()).SquaredLength() <= std::pow(general_data_.visible_range, 2)
        && map.Visible(host_.GetPosition(), food.GetPosition())) {
      food_ = &food;
      break;
    }
  }
}
