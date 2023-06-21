//
// Created by Artem Novikov on 27.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_WORKERAI_H_
#define ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_WORKERAI_H_

#include <memory>

#include "AntStateManager.h"

#include "creature/AI/event/ResourceEvent.h"
#include "creature/AI/event/HiveEvent.h"
#include "creature/AI/event/CreatureEvent.h"
#include "creature/AI/event/DefenceEvent.h"

class Ant;

class WorkerAI : public AntStateManager {
 public:
  WorkerAI(std::unique_ptr<AntState>&& state) : AntStateManager(std::move(state)) {}

  void React(EventData& data) override;

 private:
  void HiveDecision(HiveEvent& data);

  void ResourceDecision(ResourceEvent& data);

  void DefenceDecision(DefenceEvent& data);
};

#endif //ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_WORKERAI_H_
