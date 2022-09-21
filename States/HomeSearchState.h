//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_STATES_HOMESEARCHSTATE_H_
#define ANTS_STATES_HOMESEARCHSTATE_H_

#include "AntState.h"

class HomeSearchState : public AntState {
 public:
  HomeSearchState(
      SensorData& ant_senses, PheromoneData& ant_pheromone, MovementData& ant_move, const GeneralData& ant_general);

  [[nodiscard]] uint8_t Requirements() const override { return RequireHome | RequirePheromone; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Home; }

  [[nodiscard]]  StateType GetState() const override { return StateType::HomeSearch; }

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;

 protected:
  SensorData& sensor_data_;
  PheromoneData& pheromone_data_;
};

#endif //ANTS_STATES_HOMESEARCHSTATE_H_
