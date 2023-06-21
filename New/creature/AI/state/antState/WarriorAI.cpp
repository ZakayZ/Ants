//
// Created by Artem Novikov on 27.05.2023.
//

#include "creature/ant/Warrior.h"
#include "WarriorAI.h"

#include "EnemySearchState.h"

void WarriorAI::React(EventData& data) {
  switch (data.type) {
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
      std::cerr << "Warrior: no reaction set\n";
      break;
    }
  }
}

void WarriorAI::HiveDecision(HiveEvent& data) {
  assert(dynamic_cast<Warrior*>(&GetAntState().GetHost()) != nullptr);
  auto& soldier = static_cast<Warrior&>(GetAntState().GetHost());

  /// TODO heal and restore ammunition

  soldier.GetPheromoneGland().SetPheromoneType(PheromoneType::Home);
  soldier.GetPheromoneGland().Reset();

  SetState(std::make_unique<EnemySearchState>(soldier));
}

void WarriorAI::DefenceDecision(DefenceEvent& data) {

}

