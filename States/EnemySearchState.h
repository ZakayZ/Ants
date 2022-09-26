//
// Created by Artem Novikov on 23.09.2022.
//

#ifndef ANTS_STATES_ENEMYSEARCHSTATE_H_
#define ANTS_STATES_ENEMYSEARCHSTATE_H_

#include "AntData/PheromoneData.h"
#include "AntState.h"

class EnemySearchState : public AntState {
 public:
  using ::AntState::AntState;

  [[nodiscard]] uint8_t Requirements() const override { return RequireAnt | RequirePheromone; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Enemy; }

  [[nodiscard]] StateType GetState() const override { return StateType::EnemySearch; }

  [[nodiscard]] std::function<bool(Ant&)> GetProximitySensor() const override;

  [[nodiscard]] std::function<void(Ant&)> GetEnemySensor() const override;

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;

 private:
};

#endif //ANTS_STATES_ENEMYSEARCHSTATE_H_
