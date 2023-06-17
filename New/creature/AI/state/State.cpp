//
// Created by Artem Novikov on 25.05.2023.
//

#include "State.h"
#include "creature/Creature.h"
#include "StateManager.h"

void State::ChangeState(std::unique_ptr<State>&& state) {
  static_cast<StateManager&>(host_.GetAI()).SetState(std::move(state));
}
