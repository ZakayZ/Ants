//
// Created by Artem Novikov on 26.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_ATTACKSTATE_H_
#define ANTS_NEW_CREATURE_AI_STATE_ATTACKSTATE_H_

#include "AntState.h"
#include "utils/Cooldown.h"

class AttackState : public AntState {
 public:
  AttackState(Ant& host, std::weak_ptr<Creature>& target);

  void Decide(World& world, Time dt) override;

  [[nodiscard]] StateType GetType() const override { return StateType::AttackEnemy; }

 private:
  std::weak_ptr<Creature> target_;
  Cooldown attack_cooldown_;
  std::unique_ptr<AntState> previous_state_;
};

#endif //ANTS_NEW_CREATURE_AI_STATE_ATTACKSTATE_H_
