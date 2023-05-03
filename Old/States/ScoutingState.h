//
// Created by Artem Novikov on 24.09.2022.
//

#ifndef ANTS_STATES_SCOUTINGSTATE_H_
#define ANTS_STATES_SCOUTINGSTATE_H_

#include "AntState.h"

class ScoutingState : public AntState {
 public:
  using ::AntState::AntState;

  [[nodiscard]] uint8_t Requirements() const override { return RequireAnt | RequirePheromone | RequireFoodStorage; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Food; }

  [[nodiscard]] StateType GetState() const override { return StateType::Scouting; }

  [[nodiscard]] std::function<bool(Ant&)> GetProximitySensor() const override;

  [[nodiscard]] std::function<void(Ant&)> GetEnemySensor() const override;

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;
};

#endif //ANTS_STATES_SCOUTINGSTATE_H_
