//
// Created by Artem Novikov on 26.05.2023.
//

#include "RepellentState.h"

#include "creature/ant/Ant.h"
#include "world/World.h"

RepellentState::RepellentState(Ant& host)
    : HomeSearchState(host), state_duration_(host.GetGeneralData().repellent_duration) {}

void RepellentState::Decide(World& world, Time dt) {
  state_duration_.Update(dt);

  HomeSearchState::Decide(world, dt);

  if (state_duration_.Ready()) {
    ChangeState(std::make_unique<HomeSearchState>(host_));
    state_duration_.Use();
  }
}