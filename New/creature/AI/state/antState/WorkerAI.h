//
// Created by Artem Novikov on 27.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_WORKERAI_H_
#define ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_WORKERAI_H_

#include "AntStateManager.h"
#include "food/FoodSource.h"

class WorkerAI : public AntStateManager {
 public:
  WorkerAI(std::unique_ptr<AntState>&& state) : AntStateManager(std::move(state)) {}

  void AntInteraction(Ant& creature) override;

  void CreatureInteraction(Creature& creature) override;

  void HiveDecision(Hive& hive) override;

  void DefenceDecision(Creature& creature) override;

  void ResourceDecision(FoodSource& food);
};

#endif //ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_WORKERAI_H_
