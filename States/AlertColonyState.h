//
// Created by Artem Novikov on 23.09.2022.
//

#ifndef ANTS_STATES_ALERTCOLONYSTATE_H_
#define ANTS_STATES_ALERTCOLONYSTATE_H_

#include "AntData/PheromoneData.h"
#include "AntState.h"

class AlertColonyState : public AntState {
 public:
  AlertColonyState(SensorData& ant_senses, PheromoneData& ant_pheromone,
                   MovementData& ant_move, const GeneralData& ant_general);

  [[nodiscard]] uint8_t Requirements() const override { return RequireHiveStorage; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Home; }

  [[nodiscard]]  StateType GetState() const override { return StateType::AlertColony; }

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;

 private:
  SensorData& sensor_data_;
  PheromoneData& pheromone_data_;
};

#endif //ANTS_STATES_ALERTCOLONYSTATE_H_
