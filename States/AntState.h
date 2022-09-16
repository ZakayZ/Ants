//
// Created by Artem Novikov on 27.08.2022.
//

#ifndef ANTS__STATE_H_
#define ANTS__STATE_H_

#include "States.h"
#include "Requirements.h"
#include "PheromoneType.h"
#include "WorldData.h"

class AntState {
 public:
  [[nodiscard]] virtual uint8_t Requirements() const { return 0; }

  [[nodiscard]] virtual PheromoneType GetPheromoneType() const { return PheromoneType::None; }

  [[nodiscard]] virtual StateType GetState() const = 0;

  [[nodiscard]] StateType StateTransition() const { return change_state_; }

  virtual void Decide() = 0;

  virtual void Interact(WorldData& world_data, float delta_time) = 0;

  virtual ~AntState() = 0;
 protected:
  StateType change_state_ = StateType::None;
};

#endif //ANTS__STATE_H_
