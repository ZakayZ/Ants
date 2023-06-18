//
// Created by Artem Novikov on 26.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_REPELLENTSTATE_H_
#define ANTS_NEW_CREATURE_AI_STATE_REPELLENTSTATE_H_

#include "HomeSearchState.h"
#include "utils/Cooldown.h"

class RepellentState : public HomeSearchState {
 public:
  explicit RepellentState(Ant& host);

  void Decide(World& world, Time dt) final;

  [[nodiscard]] StateType GetType() const override { return StateType::RepellentPheromone; }

 private:
  Cooldown state_duration_;
};

#endif //ANTS_NEW_CREATURE_AI_STATE_REPELLENTSTATE_H_
