//
// Created by Artem Novikov on 27.08.2022.
//

#ifndef ANTS__ANT_H_
#define ANTS__ANT_H_

#include <random>

#include "Vector.h"
#include "Utils/RandomGenerator.h"

#include "AntType.h"

#include "AntData/GeneralData.h"
#include "AntData/AntData.h"
#include "AntData/MovementData.h"
#include "AntData/SensorData.h"
#include "AntData/PheromoneData.h"
#include "AntData/FoodData.h"

#include "States/FoodSearchState.h"
#include "States/HomeSearchState.h"
#include "States/GrabFoodState.h"
#include "States/StoreFoodState.h"

#include "World/Sensor.h"

class Ant {
 public:
  Ant(const Vector2f& position, size_t colony_index, const GeneralData& general_data, float pheromone_initial);

  virtual ~Ant() = 0;

  [[nodiscard]] const MovementData& GetMoveData() const { return movement_data_; }

  SensorData& GetSensorData() { return sensor_data_; }

  [[nodiscard]] const FoodData& GetFoodData() const { return food_data_; }

  [[nodiscard]] const PheromoneData& GetPheromoneData() const { return pheromone_data_; }

  [[nodiscard]] const AntData& GetAntData() const { return ant_data_; }

  [[nodiscard]] const GeneralData& GetGeneralData() const { return general_data_; }

  [[nodiscard]] float GetSize() const { return general_data_.ant_size; }

  [[nodiscard]] const Vector2f& GetPosition() const { return movement_data_.position; }

  [[nodiscard]] const Vector2f& GetTargetDirection() const { return movement_data_.target_direction; }

  [[nodiscard]] const Vector2f& GetFacingDirection() const { return movement_data_.velocity; }

  void Update(float delta_time);

  void Interact(WorldData& world_data, float delta_time);

  Sensor GetSensor();
 protected:
  void Move(float delta_time);

  void AvoidObstacle();

  void ChangeState();

  MovementData movement_data_;
  SensorData sensor_data_;
  FoodData food_data_;
  PheromoneData pheromone_data_;
  AntData ant_data_;

  const GeneralData& general_data_;

  std::unique_ptr<AntState> ant_state_;
};

#endif //ANTS__ANT_H_
