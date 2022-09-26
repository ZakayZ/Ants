//
// Created by Artem Novikov on 27.08.2022.
//

#ifndef ANTS__STATE_H_
#define ANTS__STATE_H_

#include <functional>

#include "Utils/Requirements.h"

#include "States.h"

#include "AntData/MovementData.h"
#include "AntData/GeneralData.h"
#include "AntData/SensorData.h"
#include "AntData/PheromoneData.h"

#include "World/PheromoneType.h"

class Ant;
class WorldData;

class AntState {
 public:
  AntState(SensorData& ant_sensor, PheromoneData& ant_pheromone, MovementData& ant_move, const GeneralData& ant_general);

  [[nodiscard]] virtual uint8_t Requirements() const { return 0; }

  [[nodiscard]] virtual PheromoneType GetPheromoneType() const { return PheromoneType::None; }

  [[nodiscard]] virtual StateType GetState() const = 0;

  [[nodiscard]] size_t GetColonyIndex() const { return general_data_.colony_index; }

  [[nodiscard]] virtual Vector2f GetPheromoneSensorCenter() const {
    return move_data_.position + move_data_.velocity * (general_data_.pheromone_range / general_data_.max_speed);
  }

  [[nodiscard]] virtual float GetPheromoneSensorSize() const { return general_data_.pheromone_capacity; }

  [[nodiscard]] virtual std::function<bool(Ant&)> GetProximitySensor() const;  ///  delegate it to sensor

  [[nodiscard]] virtual std::function<void(Ant&)> GetEnemySensor() const;

  [[nodiscard]] virtual Vector2f GetSensorCenter() const { return move_data_.position; };

  [[nodiscard]] virtual float GetSensorSize() const { return general_data_.visible_range; };

  [[nodiscard]] StateType StateTransition() const { return change_state_; }

  virtual void Decide(float delta_time) = 0;

  virtual void Interact(WorldData& world_data, float delta_time) = 0;

  virtual ~AntState() = 0;

 protected:
  inline void FollowPheromone(float delta_time) {
    if (sensor_data_.pheromone_strength > 0.01f) {
      move_data_.target_direction =
          Normalised(move_data_.target_direction + (delta_time * sensor_data_.pheromone_strength)
              * (sensor_data_.pheromone_center - move_data_.position));
    }
  }

  inline void Rotate() {
    move_data_.target_direction = -move_data_.target_direction;
    move_data_.velocity = -move_data_.velocity;
  }

  inline void FollowPoint(const Vector2f& point) {
    move_data_.target_direction = Normalised(point - move_data_.position);
  }

  SensorData& sensor_data_;
  PheromoneData& pheromone_data_;
  MovementData& move_data_;
  const GeneralData& general_data_;
  StateType change_state_;
};

#endif //ANTS__STATE_H_
