//
// Created by Artem Novikov on 15.09.2022.
//

#include "Ants/Ant.h"
#include "AntState.h"

AntState::AntState(Ant& host) : host_(host), general_data_(host.general_data_) {}

uint8_t AntState::Requirements() const { return 0; }

PheromoneType AntState::GetPheromoneType() const { return PheromoneType::None; }

StateType AntState::GetState() const { return StateType::None; }

size_t AntState::GetColonyIndex() const { return general_data_.colony_index; }

Vector2f AntState::GetPheromoneSensorCenter() const {
  return host_.movement_data_.position
      + host_.movement_data_.velocity * (general_data_.pheromone_range / general_data_.max_speed);
}

float AntState::GetPheromoneSensorSize() const { return general_data_.pheromone_capacity; }

std::function<bool(Ant&)> AntState::GetProximitySensor() const {
  return [&pos = host_.movement_data_.position, sq_dist = std::pow(general_data_.visible_range, 2)](Ant& ant) {
    return (pos - ant.GetPosition()).SquaredLength() <= sq_dist;
  };
}

std::function<void(Ant&)> AntState::GetEnemySensor() const { return [](Ant& ant) {}; }

Vector2f AntState::GetSensorCenter() const { return host_.movement_data_.position; }

float AntState::GetSensorSize() const { return general_data_.visible_range; }

void AntState::FollowPheromone(float delta_time) {
  if (host_.sensor_data_.pheromone_strength > 0.01f) {
    host_.movement_data_.target_direction =
        Normalised(host_.movement_data_.target_direction + (delta_time * host_.sensor_data_.pheromone_strength)
            * (host_.sensor_data_.pheromone_center - host_.movement_data_.position));
  }
}

void AntState::Rotate() {
  host_.movement_data_.target_direction = -host_.movement_data_.target_direction;
  host_.movement_data_.velocity = -host_.movement_data_.velocity;
}

void AntState::FollowPoint(const Vector2f& point)  {
  host_.movement_data_.target_direction = Normalised(point - host_.movement_data_.position);
}

AntState::~AntState() = default;
