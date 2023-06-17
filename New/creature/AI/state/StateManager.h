//
// Created by Artem Novikov on 25.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_STATEMANAGER_H_
#define ANTS_NEW_CREATURE_AI_STATE_STATEMANAGER_H_

#include <memory>

#include "creature/AI/AI.h"
#include "State.h"

class StateManager : public AI {
 public:
  StateManager(std::unique_ptr<State>&& state) : state_(std::move(state)) {}

  void SetState(std::unique_ptr<State>&& state) { state_ = std::move(state); }

  void Decide(World& world, Time dt) override { state_->Decide(world, dt); }

  std::unique_ptr<State>& GetState() { return state_; }

  std::unique_ptr<State>&& RetrieveState() { return std::move(state_); }

 protected:
  std::unique_ptr<State> state_;
};

#endif //ANTS_NEW_CREATURE_AI_STATE_STATEMANAGER_H_
