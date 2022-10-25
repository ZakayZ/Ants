//
// Created by Artem Novikov on 25.10.2022.
//

#ifndef ANTS_WORLD_MAP_H_
#define ANTS_WORLD_MAP_H_

#include "TileMap.h"
#include "PheromoneMap.h"

class Map {
 public:
  Map(size_t colonies_number, const Vector2i& map_dimensions);

  void Update(float delta_time);

  [[nodiscard]] float GetPheromone(size_t colony_index, int x, int y, PheromoneType type) const;

  [[nodiscard]] float GetPheromone(size_t colony_index, const Vector2f& position, PheromoneType type) const;

  [[nodiscard]] PheromoneMap::PheromoneInfo GetPheromoneCenter(
      size_t colony_index, const Vector2f& position, float side_length, PheromoneType type) const;

  [[nodiscard]] size_t GetWidth() const { return tile_map_.GetWidth(); }

  [[nodiscard]] size_t GetHeight() const { return tile_map_.GetHeight(); }

  void LayPheromone(size_t colony_index, const Vector2f& position, float added_pheromone, PheromoneType type);

  [[nodiscard]] bool HasObstacle(size_t x, size_t y) const;

 private:
  std::vector<PheromoneMap> colonies_pheromone_;
  TileMap tile_map_;
};

#endif //ANTS_WORLD_MAP_H_
