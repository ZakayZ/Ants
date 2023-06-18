//
// Created by Artem Novikov on 27.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_WARRIORAI_H_
#define ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_WARRIORAI_H_

#include "AntStateManager.h"

class WarriorAI : public AntStateManager {
 public:
  WarriorAI(std::unique_ptr<AntState>&& state) : AntStateManager(std::move(state)) {}

  void CreatureInteraction(std::shared_ptr<Creature> creature) override;

  void HiveDecision(Hive& hive) override;

  void DefenceDecision(Creature& creature) override;
};

#endif //ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_WARRIORAI_H_
