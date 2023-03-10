//
// Created by Artem Novikov on 27.08.2022.
//

#include "PheromoneMap.h"
#include <cmath>

PheromoneMap::PheromoneMap(Vector2i dimensions, float evaporation_rate)
    : pheromone_map_(dimensions[0] + 2, std::vector<PheromoneTile>(dimensions[1] + 2)),
      evaporation_rate_(evaporation_rate) {}

void PheromoneMap::Update(float delta_time) {
  for (auto& row : pheromone_map_) {
    for (auto& tile : row) {
      tile.cumulative_delta_time += delta_time;
      ForceUpdateTile(tile);
    }
  }
}

void PheromoneMap::UpdateTile(int x, int y, float delta_time) {
  auto& tile = pheromone_map_[x + 1][y + 1];
  tile.cumulative_delta_time += delta_time;
  ForceUpdateTile(tile);
}

float PheromoneMap::GetPheromone(int x, int y, PheromoneType type) const {
  auto& tile = pheromone_map_[x + 1][y + 1];
  UpdateTile(tile);
  return tile.pheromone[type];
}

float PheromoneMap::GetPheromone(const Vector2f& position, PheromoneType type) const {
  return GetPheromone(int(position[0]), int(position[1]), type);
}

PheromoneMap::PheromoneInfo PheromoneMap::GetPheromoneCenter(
    const Vector2f& position, float side_length, PheromoneType type) const {
  int side = int(side_length);
  const Vector2i tile_position = Vector2i(int(position[0]) + 1, int(position[1]) + 1);
  const Vector2i min_bounds = Vector2i(std::max(0, tile_position[0] - side), std::max(0, tile_position[1] - side));
  const Vector2i max_bounds = Vector2i(std::min(int(pheromone_map_.size() - 1), tile_position[0] + side),
                                       std::min(int(pheromone_map_.back().size() - 1), tile_position[1] + side));
  PheromoneInfo result;
  for (int x = min_bounds.data().x; x < max_bounds.data().x; ++x) {
    for (int y = min_bounds.data().y; y < max_bounds.data().y; ++y) {
      float strength = pheromone_map_[x][y].pheromone[type];
      result.center += Vector2f(float(x) + 0.5f, float(y) + 0.5f) *= strength;
      result.strength += strength;
    }
  }

  if (result.strength >= 0.01f) {
    result.center /= result.strength;
  }

  return result;
}

void PheromoneMap::LayPheromone(const Vector2f& position, float added_pheromone, PheromoneType type) {
  pheromone_map_[int(position[0]) + 1][int(position[1]) + 1].pheromone[type] += added_pheromone;
}

void PheromoneMap::ForceUpdateTile(PheromoneMap::PheromoneTile& tile) const {
  tile.pheromone *= (1 - tile.cumulative_delta_time * evaporation_rate_);
  tile.cumulative_delta_time = 0.f;
}

void PheromoneMap::UpdateTile(PheromoneMap::PheromoneTile& tile) const {
  if (tile.cumulative_delta_time != 0.f) {
    ForceUpdateTile(tile);
  }
}
