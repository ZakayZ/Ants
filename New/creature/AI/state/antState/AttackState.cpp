//
// Created by Artem Novikov on 26.05.2023.
//

#include "AttackState.h"
#include "creature/ant/Ant.h"

AttackState::AttackState(Ant& host, std::weak_ptr<Creature>& target)
    : AntState(host),
      target_(target),
      attack_cooldown_(host.GetGeneralData().attack_delay),
      previous_state_(host.GetStateManager().RetrieveAntState()) {}

void AttackState::Decide(World& world, Time dt) {
  attack_cooldown_.Update(dt);

  if (attack_cooldown_.Ready()) {
    attack_cooldown_.Use();

    if (target_.expired()) {
      host_.GetStateManager().SetState(std::move(previous_state_));
      return;
    }

    auto enemy = target_.lock();

    switch (enemy->GetType()) {
      case CreatureType::Ant: {
        enemy->
      }
      default: {

      }
    }
  }
}
