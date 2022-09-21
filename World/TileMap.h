//
// Created by Artem Novikov on 19.09.2022.
//

#ifndef ANTS_WORLD_TILEMAP_H_
#define ANTS_WORLD_TILEMAP_H_

#include <vector>

class TileMap {
 public:
  TileMap(const Vector2i& map_dimensions) : map_data_(map_dimensions[0], std::vector<char>(map_dimensions[1], 0)) {
    for (int i = 0; i < map_dimensions[0]; ++i) {
      map_data_[i][0] = true;
      map_data_[i].back() = true;
    }

    for (int i = 0; i < map_dimensions[1]; ++i) {
      map_data_[0][i] = true;
      map_data_.back()[i] = true;
    }

    /// TODO random map generation
  }

  [[nodiscard]] bool HasObstacle(size_t x, size_t y) const { return map_data_[x][y]; }

 private:
  std::vector<std::vector<char>> map_data_;
};

#endif //ANTS_WORLD_TILEMAP_H_
