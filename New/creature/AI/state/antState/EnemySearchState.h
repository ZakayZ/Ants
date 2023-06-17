//
// Created by Artem Novikov on 26.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_ENEMYSEARCHSTATE_H_
#define ANTS_NEW_CREATURE_AI_STATE_ENEMYSEARCHSTATE_H_

#include <optional>

#include "AntState.h"
#include "utils/Cooldown.h"

class EnemySearchState : public AntState {
 public:
  EnemySearchState(Ant& host) : AntState(host) {};

  void Decide(World& world, Time dt) override;

  [[nodiscard]] StateType GetType() const override { return StateType::EnemySearch; }

 private:
  static const Time ScanDelay;

  void FindEnemy(World& world);

  Creature* enemy_ = nullptr;
  Cooldown attack_delay_ = Cooldown(ScanDelay);
};

#endif //ANTS_NEW_CREATURE_AI_STATE_ENEMYSEARCHSTATE_H_
