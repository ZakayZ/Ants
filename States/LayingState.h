//
// Created by Artem Novikov on 14.11.2022.
//

#ifndef ANTS_STATES_LAYINGSTATE_H_
#define ANTS_STATES_LAYINGSTATE_H_

#include "AntState.h"

class LayingState : public AntState {
  using ::AntState::AntState;

  [[nodiscard]] uint8_t Requirements() const override { return RequireHiveStorage; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::None; }

  [[nodiscard]] StateType GetState() const override { return StateType::Laying; }

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;
 private:
  static const float ResetTime;

  Vector2f patrol_position_{};
  float reposition_cooldown_ = ResetTime;
};

#endif //ANTS_STATES_LAYINGSTATE_H_
