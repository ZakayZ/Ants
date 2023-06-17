//
// Created by Artem Novikov on 27.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_ANTSTATEMANAGER_H_
#define ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_ANTSTATEMANAGER_H_

#include "../StateManager.h"
#include "AntState.h"
#include "colony/Hive.h"

class AntStateManager : public StateManager {
 public:
  AntStateManager(std::unique_ptr<AntState>&& state) : StateManager(std::unique_ptr<State>(state.release())) {}

  void SetState(std::unique_ptr<AntState>&& state) { state_ = std::move(state); }

  void Decide(World& world, Time dt) override { state_->Decide(world, dt); }

  AntState& GetAntState() { return static_cast<AntState&>(*state_); }

  virtual void AntInteraction(Ant& ant) = 0;

  virtual void CreatureInteraction(Creature& creature) = 0;

  virtual void HiveDecision(Hive& hive) = 0;

  virtual void DefenceDecision(Creature& creature) = 0;
};

#endif //ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_ANTSTATEMANAGER_H_
