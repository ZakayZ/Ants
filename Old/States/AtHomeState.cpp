//
// Created by Artem Novikov on 24.09.2022.
//

#include "World/WorldData.h"
#include "AtHomeState.h"

void AtHomeState::Decide(float delta_time) {
  ///  refill
  host_.ResetPheromone();

  ///  came with food
  if (host_.GetSensorData().hive_storage.has_value() && host_.GetFoodData().carry_amount != 0) { /// TODO why there can be no hive
    host_.StoreFood();
  }

  Rotate();

  switch (general_data_.host_type) {
    case kWorker: {
      host_.ChangeState<FoodSearchState>();
      return;
    }

    case kScout: {
      host_.ChangeState<ScoutingState>();
      return;
    }

    case kSoldier: {
      host_.ChangeState<EnemySearchState>();
      return;
    }

    case kQueen: {
      host_.ChangeState<LayingState>();
      return;
    }
  }
}

void AtHomeState::Interact(WorldData& world_data, float delta_time) {}
