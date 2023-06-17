//
// Created by Artem Novikov on 26.05.2023.
//

#include "RepellentState.h"

#include "creature/ant/Ant.h"
#include "world/World.h"

void RepellentState::Decide(World& world, Time dt) {
  state_duration_.Update(dt);

  HomeSearchState::Decide(world, dt);

  if (state_duration_.Ready()) {
    ChangeState(std::make_unique<HomeSearchState>(host_));
    state_duration_.Use();
  }
}