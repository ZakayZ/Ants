//
// Created by Artem Novikov on 27.05.2023.
//

#include <cassert>

#include "creature/ant/Worker.h"
#include "WorkerAI.h"
#include "HomeSearchState.h"
#include "FoodSearchState.h"

void WorkerAI::CreatureInteraction(std::shared_ptr<Creature> creature) {
  /// TODO
}

void WorkerAI::HiveDecision(Hive& hive) {
  assert(dynamic_cast<Worker*>(&GetAntState().GetHost()) != nullptr);
  auto& worker = static_cast<Worker&>(GetAntState().GetHost());

  hive.StoreFood(worker.GetResourceSack().EmptySack().amount); /// TODO add new types of resources

  worker.GetPheromoneGland().SetPheromoneType(PheromoneType::Home);
  worker.GetPheromoneGland().Reset();

  SetState(std::make_unique<FoodSearchState>(worker));
}

void WorkerAI::DefenceDecision(Creature& creature) {
  /// TODO flee from battle or defending
}

void WorkerAI::ResourceDecision(FoodSource& food) {
  assert(dynamic_cast<Worker*>(&GetAntState().GetHost()) != nullptr);
  auto& worker = static_cast<Worker&>(GetAntState().GetHost());

  auto food_taken = food.GetFood(worker.GetResourceSack().Capacity);
  worker.GetResourceSack().Fill(food_taken, ResourceType::Food);

  worker.GetPheromoneGland().SetPheromoneType(PheromoneType::Food);
  worker.GetPheromoneGland().Reset();

  SetState(std::make_unique<HomeSearchState>(worker));
}
