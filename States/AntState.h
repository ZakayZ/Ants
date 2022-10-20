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
  AntState(Ant& host);

  [[nodiscard]] virtual uint8_t Requirements() const;

  [[nodiscard]] virtual PheromoneType GetPheromoneType() const;

  [[nodiscard]] virtual StateType GetState() const;

  [[nodiscard]] size_t GetColonyIndex() const;

  [[nodiscard]] virtual Vector2f GetPheromoneSensorCenter() const;

  [[nodiscard]] virtual float GetPheromoneSensorSize() const;

  [[nodiscard]] virtual std::function<bool(Ant&)> GetProximitySensor() const;  ///  delegate it to sensor

  [[nodiscard]] virtual std::function<void(Ant&)> GetEnemySensor() const;

  [[nodiscard]] virtual Vector2f GetSensorCenter() const;

  [[nodiscard]] virtual float GetSensorSize() const;

  virtual void Decide(float delta_time) = 0;

  virtual void Interact(WorldData& world_data, float delta_time) = 0;

  virtual ~AntState() = 0;

 protected:
  void FollowPheromone(float delta_time);

  void Rotate();

  void FollowPoint(const Vector2f& point);

  Ant& host_;
  const GeneralData& general_data_;
};

#endif //ANTS__STATE_H_
