//
// Created by Artem Novikov on 23.09.2022.
//

#ifndef ANTS_STATES_ATTACKENEMYSTATE_H_
#define ANTS_STATES_ATTACKENEMYSTATE_H_

#include <optional>

#include "AntData/FightData.h"
#include "AntState.h"

class AttackEnemyState : public AntState {
 public:
  using ::AntState::AntState;

  [[nodiscard]] uint8_t Requirements() const override { return RequireAnt; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Enemy; }

  [[nodiscard]] StateType GetState() const override { return StateType::AttackEnemy; }

  [[nodiscard]] std::function<bool(Ant&)> GetProximitySensor() const override;

  [[nodiscard]] std::function<void(Ant&)> GetEnemySensor() const override;

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;

 private:
  float attack_cooldown_{};
};

#endif //ANTS_STATES_ATTACKENEMYSTATE_H_
