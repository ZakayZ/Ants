//
// Created by Artem Novikov on 03.05.2023.
//

#include "NaivePheromoneMap.h"

NaivePheromoneMap::NaivePheromoneMap(Vector2i dimensions, Vector2f scale, Float diffusion_rate, Float evaporation_rate)
    : tiles_(dimensions[0], std::vector<PheromoneTile>(dimensions[1])),
      scale_(scale),
      diffusion_rate_(diffusion_rate),
      evaporation_rate_(evaporation_rate) {}

PheromoneList NaivePheromoneMap::GetPheromone(const BoundaryBox<Float, 2>& box, PheromoneType type) {
  return {tiles_, ToMap(box.GetLeft()), ToMap(box.GetRight())};
}

void NaivePheromoneMap::AddPheromone(const Vector<Float, 2>& position, Float strength, PheromoneType type) {
  auto tile_position = ToMap(position);
  tiles_[tile_position[0]][tile_position[1]].pheromone[type] += strength;
  // TODO update
}

PheromoneData NaivePheromoneMap::GetPheromoneStrength(const BoundaryBox<Float, 2>& box, PheromoneType type) {
  auto l = ToMap(box.GetLeft());
  auto r = ToMap(box.GetRight());
  r[0] = std::min(r[0] + 1, int(tiles_.size()));
  r[1] = std::min(r[1] + 1, int(tiles_.back().size()));
  l[0] = std::max(l[0], 0);
  l[0] = std::max(l[1], 0);

  PheromoneData data{};

  for (int x = l[0]; x < r[0]; ++x) {
    for (int y = l[1]; y < r[1]; ++y) {
      auto delta = tiles_[x][y].pheromone[type];
      data.total_strength += delta;
      data.mean_position += Vector2f{delta * scale_[0] * (float(x) + 0.5f), delta * scale_[1] * (float(y) + 0.5f)};
      // TODO update
    }
  }

  if (data.total_strength != 0) {
    data.mean_position /= data.total_strength;
  }

  return data;
}

void NaivePheromoneMap::Update(Time dt) {
  // TODO diffusion
}

Vector2i NaivePheromoneMap::ToMap(const Position& position) const {
  return {int(position[0] / scale_[0]), int(position[1] / scale_[1])};
}


