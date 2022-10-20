//
// Created by Artem Novikov on 24.09.2022.
//

#ifndef ANTS_STATES_ATHOMESTATE_H_
#define ANTS_STATES_ATHOMESTATE_H_

#include "AntState.h"

class AtHomeState : public AntState {
 public:
  using ::AntState::AntState;

  [[nodiscard]] uint8_t Requirements() const override { return RequireHiveStorage; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::None; }

  [[nodiscard]] StateType GetState() const override { return StateType::Idle; }

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;
};

#endif //ANTS_STATES_ATHOMESTATE_H_
