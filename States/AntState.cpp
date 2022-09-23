//
// Created by Artem Novikov on 15.09.2022.
//

#include "AntState.h"
#include "Ants/Ant.h"

AntState::AntState(MovementData& ant_move, const GeneralData& ant_general)
    : move_data_(ant_move), general_data_(ant_general), change_state_(StateType::None) {}

std::function<bool(Ant&)> AntState::GetProximitySensor() const {
  return [&pos = move_data_.position, sq_dist = std::pow(general_data_.visible_range, 2)](Ant& ant) {
    return (pos - ant.GetPosition()).SquaredLength() <= sq_dist;
  };
}

std::function<void(Ant&)> AntState::GetEnemySensor() const {
  return [](Ant& ant) {};
}

void AntState::FollowPheromone(SensorData& sensor_data, float delta_time) {
  if (sensor_data.pheromone_strength > 0.01f) {
    move_data_.target_direction =
        Normalised(move_data_.target_direction + (delta_time * sensor_data.pheromone_strength)
            * (sensor_data.pheromone_center - move_data_.position));
  }
}

void AntState::Rotate() {
  move_data_.target_direction = -move_data_.target_direction;
  move_data_.velocity = -move_data_.velocity;
}

void AntState::FollowPoint(const Vector2f& point) {
  move_data_.target_direction = Normalised(point - move_data_.position);
}

AntState::~AntState() = default;
