//
// Created by Artem Novikov on 27.05.2023.
//

#include "creature/ant/Warrior.h"
#include "WarriorAI.h"

#include "EnemySearchState.h"

void WarriorAI::CreatureInteraction(std::shared_ptr<Creature> creature) {
  /// TODO
}

void WarriorAI::HiveDecision(Hive& hive) {
  assert(dynamic_cast<Warrior*>(&GetAntState().GetHost()) != nullptr);
  auto& soldier = static_cast<Warrior&>(GetAntState().GetHost());

  /// TODO heal and restore ammunition

  soldier.GetPheromoneGland().SetPheromoneType(PheromoneType::Home);
  soldier.GetPheromoneGland().Reset();

  SetState(std::make_unique<EnemySearchState>(soldier));
}

void WarriorAI::DefenceDecision(Creature& creature) {
  /// TODO attack enemy
}

