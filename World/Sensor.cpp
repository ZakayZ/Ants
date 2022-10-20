//
// Created by Artem Novikov on 02.09.2022.
//

#include "WorldData.h"
#include "Sensor.h"
#include "BoundaryBox.h"

Sensor::Sensor(const std::unique_ptr<AntState>& ant_state, const GeneralData& ant_general,
               const MovementData& ant_position, SensorData& sensor_data)
    : state_data_(ant_state), general_data_(ant_general), movement_data_(ant_position), data_(sensor_data) {}

void Sensor::Sense(WorldData& world_data) {
  DetectWalls(world_data);

  auto requirements = state_data_->Requirements();
  if (requirements & RequireHiveStorage) {
    DetectHome(world_data);
  }

  if (requirements & RequireFoodStorage) {
    DetectFood(world_data);
  }

  if (requirements & RequirePheromone) {
    DetectPheromone(world_data);
  }

  if (requirements & RequireAnt) {
    DetectAnts(world_data);
  }
}

void Sensor::DetectWalls(WorldData& world_data) {
  data_.is_wall_ahead = false;
  Vector2i tile_position = movement_data_.position;

  if (world_data.map_.HasObstacle(tile_position[0] + 1, tile_position[1])) {
    data_.is_wall_ahead = true;
    data_.wall_data[0] = 1.f;
  }

  if (tile_position[0] <= 0 || world_data.map_.HasObstacle(tile_position[0] - 1, tile_position[1])) {
    data_.is_wall_ahead = true;
    data_.wall_data[0] = -1.f;
  }

  if (world_data.map_.HasObstacle(tile_position[0], tile_position[1] + 1)) {
    data_.is_wall_ahead = true;
    data_.wall_data[1] = 1.f;
  }

  if (tile_position[1] <= 0 || world_data.map_.HasObstacle(tile_position[0], tile_position[1] - 1)) {
    data_.is_wall_ahead = true;
    data_.wall_data[1] = -1.f;
  }
}

void Sensor::DetectHome(WorldData& world_data) {
  data_.hive_storage.reset();
  data_.hive_storage.reset();

  for (auto& hive : world_data.hive_map_[state_data_->GetColonyIndex()]) {
    auto sq_length = (hive.GetPosition() - movement_data_.position).SquaredLength();

    if (sq_length <= std::pow(general_data_.ant_size + hive.GetSize(), 2)) {
      data_.hive_storage = std::make_optional(&hive.GetStorage());
      data_.hive_position = std::make_optional(hive.GetPosition());
      break;
    }

    if (sq_length <= std::pow(general_data_.visible_range + hive.GetSize(), 2)) {
      data_.hive_position = std::make_optional(hive.GetPosition());
      break;
    }
  }
}

void Sensor::DetectFood(WorldData& world_data) {
  data_.food_source.reset();
  data_.food_position.reset();

  for (auto& food_source : world_data.food_map_) {
    auto sq_length = (food_source.GetPosition() - movement_data_.position).SquaredLength();

    if (sq_length <= std::pow(general_data_.ant_size + food_source.GetSize(), 2)) {
      data_.food_source = std::make_optional(&food_source);
      data_.food_position = std::make_optional(food_source.GetPosition());
      break;
    }

    if (sq_length <= std::pow(general_data_.visible_range + food_source.GetSize(), 2)) {
      data_.food_position = std::make_optional(food_source.GetPosition());
      break;
    }
  }
}

void Sensor::DetectPheromone(WorldData& world_data) {
  auto pheromone_data = world_data.pheromone_map_.GetPheromoneCenter(general_data_.colony_index,
                                                                     state_data_->GetPheromoneSensorCenter(),
                                                                     state_data_->GetPheromoneSensorSize(),
                                                                     state_data_->GetPheromoneType());
  data_.pheromone_strength = pheromone_data.strength;
  data_.pheromone_center = pheromone_data.center;
}

void Sensor::DetectAnts(WorldData& world_data) {
  data_.target_ant.reset();
  auto size = state_data_->GetSensorSize();
  auto center = state_data_->GetSensorCenter();
  BoundaryBox2f box({center[0] - size, center[1] - size}, {center[0] + size, center[1] + size});
  world_data.ant_map_.ApplyInBox(box, state_data_->GetProximitySensor(), state_data_->GetEnemySensor());
}
