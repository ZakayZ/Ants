//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_STATES_FOODSEARCHSTATE_H_
#define ANTS_STATES_FOODSEARCHSTATE_H_

#include "AntData/SensorData.h"
#include "AntData/PheromoneData.h"
#include "AntState.h"

class FoodSearchState : public AntState {
 public:
  FoodSearchState(
      SensorData& ant_senses, PheromoneData& ant_pheromone, MovementData& ant_move, const GeneralData& ant_general)
      : AntState(ant_move, ant_general), sensor_data_(ant_senses), pheromone_data_(ant_pheromone) {}

  [[nodiscard]] uint8_t Requirements() const override { return RequireFood | RequirePheromone | RequireAnt; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Food; }

  [[nodiscard]] StateType GetState() const override { return StateType::FoodSearch; }

  [[nodiscard]] std::function<bool(Ant&)> GetProximitySensor() const override;

  [[nodiscard]] std::function<void(Ant&)> GetEnemySensor() const override;

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;

 private:
  SensorData& sensor_data_;
  PheromoneData& pheromone_data_;
};

#endif //ANTS_STATES_FOODSEARCHSTATE_H_
