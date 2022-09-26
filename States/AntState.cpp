//
// Created by Artem Novikov on 15.09.2022.
//

#include "Ants/Ant.h"
#include "AntState.h"

AntState::AntState(SensorData& ant_sensor, PheromoneData& ant_pheromone,
                   MovementData& ant_move, const GeneralData& ant_general)
    : sensor_data_(ant_sensor),
      pheromone_data_(ant_pheromone),
      move_data_(ant_move),
      general_data_(ant_general),
      change_state_(StateType::None) {}

std::function<bool(Ant&)> AntState::GetProximitySensor() const {
  return [&pos = move_data_.position, sq_dist = std::pow(general_data_.visible_range, 2)](Ant& ant) {
    return (pos - ant.GetPosition()).SquaredLength() <= sq_dist;
  };
}

std::function<void(Ant&)> AntState::GetEnemySensor() const {
  return [](Ant& ant) {};
}

AntState::~AntState() = default;
