//
// Created by Artem Novikov on 15.09.2022.
//

#include "AntState.h"
#include "Ants/Ant.h"

AntState::AntState(MovementData& ant_move, const GeneralData& ant_general)
    : move_data_(ant_move), general_data_(ant_general), change_state_(StateType::None) {}

std::function<bool(const Ant&)> AntState::GetProximitySensor() const {
  return [&pos = move_data_.position, &dist = general_data_.visible_range](const Ant& ant) {
    return (pos - ant.GetPosition()).SquaredLength() <= dist * dist;
  };
}

std::function<void(const Ant&)> AntState::GetEnemySensor() const {
  return [](const Ant& ant) {};
}

AntState::~AntState() = default;
