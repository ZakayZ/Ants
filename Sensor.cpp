//
// Created by Artem Novikov on 02.09.2022.
//

#include "Sensor.h"

Sensor::Sensor(const std::unique_ptr<AntState>& ant_state, const GeneralData& ant_general,
               const MovementData& ant_position, SensorData& ant_data)
    : state_data_(ant_state), general_data_(ant_general), movement_data_(ant_position), data_(ant_data) {}

void Sensor::Sense(WorldData& world_data) {
  DetectWalls(world_data);

  auto requirements = state_data_->Requirements();
  if (requirements & RequireHiveStorage) {
    DetectHome(world_data);
  }

  if (requirements & RequireFoodStorage) {
    DetectFood(world_data);
  }

  if (requirements & RequireFood) {
    DetectFoodPosition(world_data);
  }

  if (requirements & RequireHome) {
    DetectHomePosition(world_data);
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
  if (world_data.map_[tile_position[0] + 1][tile_position[1]]) {
    data_.is_wall_ahead = true;
    data_.wall_data[0] = 1.f;
  }

  if (world_data.map_[tile_position[0] - 1][tile_position[1]]) {
    data_.is_wall_ahead = true;
    data_.wall_data[0] = -1.f;
  }

  if (world_data.map_[tile_position[0]][tile_position[1] + 1]) {
    data_.is_wall_ahead = true;
    data_.wall_data[1] = 1.f;
  }

  if (world_data.map_[tile_position[0]][tile_position[1] - 1]) {
    data_.is_wall_ahead = true;
    data_.wall_data[1] = -1.f;
  }
}

void Sensor::DetectHome(WorldData& world_data) {
  data_.hive_storage.reset();
  for (auto& hive : world_data.hive_map_) {
    if ((hive.GetPosition() - movement_data_.position).SquaredLength() <=
        std::pow(general_data_.ant_size + hive.GetSize(), 2)) {
      data_.hive_storage = {&hive.GetStorage()};
      break;
    }
  }
}

void Sensor::DetectFood(WorldData& world_data) {
  data_.food_source.reset();
  for (auto& food_source : world_data.food_map_) {
    if ((food_source.GetPosition() - movement_data_.position).SquaredLength() <=
        std::pow(general_data_.ant_size + food_source.GetSize(), 2)) {
      data_.food_source = {&food_source};
      break;
    }
  }
}

void Sensor::DetectFoodPosition(WorldData& world_data) {
  data_.food_position.reset();
  for (auto& food_source : world_data.food_map_) {
    if ((food_source.GetPosition() - movement_data_.position).SquaredLength() <=
        std::pow(general_data_.visible_range + food_source.GetSize(), 2)) {
      data_.food_position = std::make_optional(food_source.GetPosition());
      break;
    }
  }
}

void Sensor::DetectHomePosition(WorldData& world_data) {
  data_.hive_position.reset();
  for (auto& hive : world_data.hive_map_) {
    if ((hive.GetPosition() - movement_data_.position).SquaredLength() <=
        std::pow(general_data_.visible_range + hive.GetSize(), 2)) {
      data_.hive_position = std::make_optional(hive.GetPosition());
      break;
    }
  }
}

void Sensor::DetectPheromone(WorldData& world_data) {
  auto pheromone_data = world_data.pheromone_map_.GetPheromoneCenter(
      movement_data_.position + (movement_data_.target_direction + movement_data_.velocity / general_data_.max_speed) * general_data_.pheromone_range,
      general_data_.pheromone_range,
      state_data_->GetPheromoneType());
  data_.pheromone_strength = pheromone_data.strength;
  data_.pheromone_center = pheromone_data.center;
}

void Sensor::DetectAnts(WorldData& world_data) {  /// TODO

}
