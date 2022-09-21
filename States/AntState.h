//
// Created by Artem Novikov on 27.08.2022.
//

#ifndef ANTS__STATE_H_
#define ANTS__STATE_H_

#include "States.h"
#include "Utils/Requirements.h"
#include "AntData/MovementData.h"
#include "AntData/GeneralData.h"
#include "World/PheromoneType.h"
#include "World/WorldData.h"

class AntState {
 public:
  AntState(MovementData& ant_move, const GeneralData& ant_general);

  [[nodiscard]] virtual uint8_t Requirements() const { return 0; }

  [[nodiscard]] virtual PheromoneType GetPheromoneType() const { return PheromoneType::None; }

  [[nodiscard]] virtual StateType GetState() const = 0;

  [[nodiscard]] virtual Vector2f GetSensorCenter() const {
    return move_data_.position + move_data_.velocity * (general_data_.pheromone_range / general_data_.max_speed);
  }

  [[nodiscard]] virtual float GetSensorSize() const { return general_data_.pheromone_capacity; }

  [[nodiscard]] StateType StateTransition() const { return change_state_; }

  virtual void Decide(float delta_time) = 0;

  virtual void Interact(WorldData& world_data, float delta_time) = 0;

  virtual ~AntState() = 0;

 protected:
  MovementData& move_data_;
  const GeneralData& general_data_;
  StateType change_state_;
};

#endif //ANTS__STATE_H_
