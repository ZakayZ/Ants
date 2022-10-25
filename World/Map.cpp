//
// Created by Artem Novikov on 25.10.2022.
//

#include "Map.h"

Map::Map(size_t colonies_number, const Vector2i& map_dimensions)
    : colonies_pheromone_(colonies_number, PheromoneMap(map_dimensions)), tile_map_(map_dimensions) {}

void Map::Update(float delta_time) {
//  /// slow way
//  for (auto& pheromone_map : colonies_pheromone_) {
//    pheromone_map.Update(delta_time);
//  }

  for (auto& pheromone_map : colonies_pheromone_) {
    for (size_t x = 0; x < GetWidth(); ++x) {
      for (size_t y = 0; y < GetHeight(); ++y) {
        if (!tile_map_.HasObstacle(x, y)) {
          pheromone_map.UpdateTile(x, y, delta_time);
        }
      }
    }
  }
}

float Map::GetPheromone(size_t colony_index, int x, int y, PheromoneType type) const {
  return colonies_pheromone_[colony_index].GetPheromone(x, y, type);
}

float Map::GetPheromone(size_t colony_index, const Vector2f& position, PheromoneType type) const {
  return colonies_pheromone_[colony_index].GetPheromone(position, type);
}

PheromoneMap::PheromoneInfo Map::GetPheromoneCenter(
    size_t colony_index, const Vector2f& position, float side_length, PheromoneType type) const {
  return colonies_pheromone_[colony_index].GetPheromoneCenter(position, side_length, type);
}

void Map::LayPheromone(size_t colony_index, const Vector2f& position, float added_pheromone, PheromoneType type) {
  colonies_pheromone_[colony_index].LayPheromone(position, added_pheromone, type);
}

bool Map::HasObstacle(size_t x, size_t y) const {
  return tile_map_.HasObstacle(x, y);
}
