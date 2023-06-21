//
// Created by Artem Novikov on 27.05.2023.
//

#include <cassert>
#include <iostream>

#include "creature/ant/Worker.h"
#include "WorkerAI.h"
#include "HomeSearchState.h"
#include "FoodSearchState.h"

void WorkerAI::React(EventData& data) {
  switch (data.type) {
    case EventType::Resource: {
      assert(dynamic_cast<ResourceEvent*>(&data) != nullptr);
      ResourceDecision(static_cast<ResourceEvent&>(data));
      break;
    }
    case EventType::Hive: {
      assert(dynamic_cast<HiveEvent*>(&data) != nullptr);
      HiveDecision(static_cast<HiveEvent&>(data));
      break;
    }
    case EventType::Creature: {
      assert(dynamic_cast<CreatureEvent*>(&data) != nullptr);
      /// TODO
      break;
    }
    case EventType::Attacked: {
      assert(dynamic_cast<DefenceEvent*>(&data) != nullptr);
      DefenceDecision(static_cast<DefenceEvent&>(data));
      break;
    }
    default: {
      std::cerr << "Worker: no reaction set\n";
      break;
    }
  }
}

void WorkerAI::HiveDecision(HiveEvent& data) {
  assert(dynamic_cast<Worker*>(&GetAntState().GetHost()) != nullptr);
  auto& worker = static_cast<Worker&>(GetAntState().GetHost());

  data.hive.StoreFood(worker.GetResourceSack().EmptySack().amount); /// TODO add new types of resources

  worker.GetPheromoneGland().SetPheromoneType(PheromoneType::Home);
  worker.GetPheromoneGland().Reset();

  SetState(std::make_unique<FoodSearchState>(worker));
}

void WorkerAI::ResourceDecision(ResourceEvent& data) {
  assert(dynamic_cast<Worker*>(&GetAntState().GetHost()) != nullptr);
  auto& worker = static_cast<Worker&>(GetAntState().GetHost());

  auto food_taken = data.food_source.GetFood(worker.GetResourceSack().Capacity);
  worker.GetResourceSack().Fill(food_taken, ResourceType::Food);

  worker.GetPheromoneGland().SetPheromoneType(PheromoneType::Food);
  worker.GetPheromoneGland().Reset();

  SetState(std::make_unique<HomeSearchState>(worker));
}

void WorkerAI::DefenceDecision(DefenceEvent& data) {
  /// TODO
}
