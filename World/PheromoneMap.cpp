//
// Created by Artem Novikov on 27.08.2022.
//

#include "PheromoneMap.h"
#include <cmath>

PheromoneMap::PheromoneMap(Vector2i dimensions, size_t colonies_number, float evaporation_rate)
    : pheromone_map_(dimensions[0] + 2, std::vector<PheromoneTile>(dimensions[1] + 2, PheromoneTile(colonies_number))),
      evaporation_rate_(evaporation_rate) {}

void PheromoneMap::Update(float delta_time) {
  for (auto& row : pheromone_map_) {
    for (auto& tile : row) {
      UpdateTileTime(tile, delta_time);
      ForceUpdateTile(tile);
    }
  }
}

float PheromoneMap::GetPheromone(int x, int y, size_t colony_index, PheromoneType type) const {
  auto& tile = pheromone_map_[x + 1][y + 1];
  UpdateTile(tile, colony_index);
  return tile.pheromone[colony_index][type];
}

float PheromoneMap::GetPheromone(const Vector2f& position, size_t colony_index, PheromoneType type) const {
  return GetPheromone(int(position[0]), int(position[1]), colony_index, type);
}

PheromoneMap::PheromoneInfo PheromoneMap::GetPheromoneCenter(
    const Vector2f& position, float side_length, size_t colony_index, PheromoneType type) const {
  int side = int(side_length);
  const Vector2i tile_position = Vector2i(int(position[0]) + 1, int(position[1]) + 1);
  const Vector2i min_bounds = Vector2i(std::max(0, tile_position[0] - side), std::max(0, tile_position[1] - side));
  const Vector2i max_bounds = Vector2i(std::min(int(pheromone_map_.size() - 1), tile_position[0] + side),
                                       std::min(int(pheromone_map_.back().size() - 1), tile_position[1] + side));
  PheromoneInfo result;
  for (int x = min_bounds.data().x; x < max_bounds.data().x; ++x) {
    for (int y = min_bounds.data().y; y < max_bounds.data().y; ++y) {
      float strength = pheromone_map_[x][y].pheromone[colony_index][type];
      result.center += Vector2f(float(x) + 0.5f, float(y) + 0.5f) *= strength;
      result.strength += strength;
    }
  }

  if (result.strength >= 0.01f) {
    result.center /= result.strength;
  }

  return result;
}

void PheromoneMap::LayPheromone(
    const Vector2f& position, float added_pheromone, size_t colony_index, PheromoneType type) {
  pheromone_map_[int(position[0]) + 1][int(position[1]) + 1].pheromone[colony_index][type] += added_pheromone;
}

void PheromoneMap::UpdateTileTime(PheromoneMap::PheromoneTile& tile, float delta_time) const {
  for (auto& time : tile.cumulative_delta_time) {
    time += delta_time;
  }
}

void PheromoneMap::ForceUpdateTile(PheromoneMap::PheromoneTile& tile, size_t colony_index) const {
  tile.pheromone[colony_index] *= (1 - evaporation_rate_ * tile.cumulative_delta_time[colony_index]);
  tile.cumulative_delta_time[colony_index] = 0.f;
}

void PheromoneMap::ForceUpdateTile(PheromoneMap::PheromoneTile& tile) const {
  for (size_t i = 0; i < tile.pheromone.size(); ++i) {
    ForceUpdateTile(tile, i);
  }
}

void PheromoneMap::UpdateTile(PheromoneMap::PheromoneTile& tile, size_t colony_index) const {
  if (tile.cumulative_delta_time[colony_index] >= 0.01f) {
    ForceUpdateTile(tile, colony_index);
  }
}

void PheromoneMap::UpdateTile(PheromoneMap::PheromoneTile& tile) const {
  for (size_t i = 0; i < tile.pheromone.size(); ++i) {
    UpdateTile(tile, i);
  }
}
