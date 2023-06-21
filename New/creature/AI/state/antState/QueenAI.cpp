//
// Created by Artem Novikov on 27.05.2023.
//

#include "QueenAI.h"
/// TODO

void QueenAI::React(EventData& data) {
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
      std::cerr << "Queen: no reaction set\n";
      break;
    }
  }
}

void QueenAI::HiveDecision(HiveEvent& data) {
  /// TODO
}

void QueenAI::DefenceDecision(DefenceEvent& data) {
  /// TODO
}
