//
// Created by Artem Novikov on 24.09.2022.
//

#ifndef ANTS_STATES_DEFENDINGSTATE_H_
#define ANTS_STATES_DEFENDINGSTATE_H_

#include "AntData/FightData.h"
#include "AntState.h"

class DefendingState : public AntState{
 public:
  DefendingState(StateType last_state, SensorData& ant_sensor, PheromoneData& ant_pheromone,
                 MovementData& ant_move, const GeneralData& ant_general);

  [[nodiscard]] uint8_t Requirements() const override { return RequireAnt; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Enemy; }

  [[nodiscard]] StateType GetState() const override { return StateType::Defending; }

  [[nodiscard]] std::function<bool(Ant&)> GetProximitySensor() const override;

  [[nodiscard]] std::function<void(Ant&)> GetEnemySensor() const override;

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;

 private:
  StateType last_state_;
  float attack_cooldown_ = 0.f;
};

#endif //ANTS_STATES_DEFENDINGSTATE_H_
