//
// Created by Artem Novikov on 26.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_ATTACKSTATE_H_
#define ANTS_NEW_CREATURE_AI_STATE_ATTACKSTATE_H_

#include "AntState.h"

class AttackState : public AntState {
 public:
  AttackState(Ant& host) : AntState(host) {}

  void Decide(World& world, Time dt) override;

  [[nodiscard]] StateType GetType() const override { return StateType::AttackEnemy; }

 private:
};

#endif //ANTS_NEW_CREATURE_AI_STATE_ATTACKSTATE_H_
