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
  using ::AntState::AntState;

  [[nodiscard]] uint8_t Requirements() const override { return RequireFoodStorage | RequirePheromone; }

  [[nodiscard]] PheromoneType GetPheromoneType() const override { return PheromoneType::Food; }

  [[nodiscard]] StateType GetState() const override { return StateType::FoodSearch; }

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;
};

#endif //ANTS_STATES_FOODSEARCHSTATE_H_
