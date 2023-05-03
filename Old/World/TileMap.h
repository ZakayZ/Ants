//
// Created by Artem Novikov on 19.09.2022.
//

#ifndef ANTS_WORLD_TILEMAP_H_
#define ANTS_WORLD_TILEMAP_H_

#include <vector>

#include "Vector.h"
#include "MapGenerator.h"

class TileMap {
 public:
  using TileType = char;

  TileMap(const Vector2i& map_dimensions) : map_data_(map_dimensions[0], std::vector<TileType>(map_dimensions[1], 0)) {
    static const size_t base_map = 100;
    MapGenerator generator(base_map, base_map);
    generator.Generate(0.38, 6);
    generator.IterateMap(10);
    generator.ConnectClosest(1);
    generator.FillUnconnected();  ///  Just in case
    generator.SquashFloating(0.01f);
    generator.Resize(map_dimensions[0], map_dimensions[1]);
    generator.IterateMap(10);  /// smooth out
    const auto& map = generator.GetMap();
    for (size_t x = 0; x < map_data_.size(); ++x) {
      for (size_t y = 0; y < map_data_[x].size(); ++y) {
        map_data_[x][y] = static_cast<TileType>(MapGenerator::IsWall(map[x][y]));
      }
    }
  }

  [[nodiscard]] bool HasObstacle(size_t x, size_t y) const { return map_data_[x][y]; }

  [[nodiscard]] size_t GetHeight() const { return map_data_.back().size(); }

  [[nodiscard]] size_t GetWidth() const { return map_data_.size(); }

 private:
  std::vector<std::vector<TileType>> map_data_;
};

#endif //ANTS_WORLD_TILEMAP_H_
