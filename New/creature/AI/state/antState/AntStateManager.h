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

  AntState& GetAntState() {
    assert(dynamic_cast<AntState*>(&*state_) != nullptr);
    return static_cast<AntState&>(*state_);
  }

  AntState* RetrieveAntState() {
    assert(dynamic_cast<AntState*>(&*state_) != nullptr);
    return static_cast<AntState*>(state_.release());
  }
};

#endif //ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_ANTSTATEMANAGER_H_
