//
// Created by Artem Novikov on 02.09.2022.
//

#ifndef ANTS__SENSOR_H_
#define ANTS__SENSOR_H_

#include <memory>

#include "States/AntState.h"
#include "AntData/SensorData.h"
#include "AntData/GeneralData.h"
#include "AntData/MovementData.h"
#include "WorldData.h"

class Sensor {
 public:
  Sensor(const std::unique_ptr<AntState>& ant_state, const GeneralData& ant_general,
         const MovementData& ant_position, SensorData& ant_data);

  void Sense(WorldData& world_data);

 private:
  void DetectWalls(WorldData& world_data);
  void DetectHome(WorldData& world_data);
  void DetectFood(WorldData& world_data);
  void DetectFoodPosition(WorldData& world_data);
  void DetectHomePosition(WorldData& world_data);
  void DetectPheromone(WorldData& world_data);
  void DetectAnts(WorldData& world_data);

  const std::unique_ptr<AntState>& state_data_;
  const GeneralData& general_data_;
  const MovementData& movement_data_;
  SensorData& data_;
};

#endif //ANTS__SENSOR_H_
