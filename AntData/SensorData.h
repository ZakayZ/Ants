//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_ANTDATA_SENSORDATA_H_
#define ANTS_ANTDATA_SENSORDATA_H_

#include <optional>

#include "PheromoneType.h"
#include "Vector.h"
#include "HiveStorage.h"
#include "FoodSource.h"

struct SensorData {
  std::optional<Vector2f> food_position;

  std::optional<FoodSource*> food_source;

  std::optional<Vector2f> hive_position;

  std::optional<HiveStorage*> hive_storage;

  float pheromone_strength;
  Vector2f pheromone_center;

  bool is_wall_ahead;
  Vector2f wall_data;
};

#endif //ANTS_ANTDATA_SENSORDATA_H_