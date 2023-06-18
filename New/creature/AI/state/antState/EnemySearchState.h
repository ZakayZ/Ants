//
// Created by Artem Novikov on 26.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_ENEMYSEARCHSTATE_H_
#define ANTS_NEW_CREATURE_AI_STATE_ENEMYSEARCHSTATE_H_

#include <memory>
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

  std::weak_ptr<Creature> enemy_;
  Cooldown scan_cooldown_ = Cooldown(ScanDelay);
};

#endif //ANTS_NEW_CREATURE_AI_STATE_ENEMYSEARCHSTATE_H_
