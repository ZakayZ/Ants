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

float Map::RayCast(const Vector2f& origin, const Vector2f& direction, float length) const {
  auto x0 = static_cast<size_t>(origin[0]); /// TODO refactor
  auto y0 = static_cast<size_t>(origin[0]);
  if (direction[0] > 0.f) {
    auto x1 = std::min(static_cast<size_t>(origin[0] + length * direction[0]) + 1, GetWidth());
    for (auto x = x0; x < x1; ++x) {
      if (HasObstacle(x, y0)) {
        return float(x) * length / float(x1 - x0);
      }
    }
  }
  if (direction[0] < 0.f) {
    auto x1 = x0 - std::min(static_cast<size_t>(origin[0] - length * direction[0]) + 1, x0);
    for (auto x = x0 + 1; x > x1; --x) {
      if (HasObstacle(x - 1, y0)) {
        return float(x - 1) * length / float(x0 - x1);
      }
    }
  }
  if (direction[1] > 0.f) {
    auto y1 = std::min(static_cast<size_t>(origin[1] + length * direction[1]) + 1, GetHeight());
    for (auto y = y0; y < y1; ++y) {
      if (HasObstacle(x0, y)) {
        return float(y) * length / float(y1 - y0);
      }
    }
  }
  if (direction[1] < 0.f) {
    auto y1 = y0 - std::min(static_cast<size_t>(origin[1] - length * direction[1]) + 1, y0);
    for (auto y = y0 + 1; y > y1; --y) {
      if (HasObstacle(x0, y - 1)) {
        return float(y - 1) * length / float(y0 - y1);
      }
    }
  }
  return length;
}

float Map::RayCast(const Vector2f& origin, const Vector2f& ray) const {
  auto length = ray.Length();
  return RayCast(origin, ray / length, length);
}

bool Map::HasObstacle(size_t x, size_t y) const {
  return tile_map_.HasObstacle(x, y);
}
