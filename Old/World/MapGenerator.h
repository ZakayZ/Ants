//
// Created by Artem Novikov on 25.10.2022.
//

#ifndef ANTS_WORLD_MAPGENERATOR_H_
#define ANTS_WORLD_MAPGENERATOR_H_

#include <vector>

class MapGenerator {
 public:
  using value_type = uint32_t;

  MapGenerator(const std::vector<std::vector<value_type>>& initial_states);

  MapGenerator(size_t width, size_t height);

  void Generate(float density, uint32_t seed = 0);

  void IterateMap(size_t iterations, size_t alive_threshold = 3, size_t revive_threshold = 4);

  void IdentifyRooms();

  void FillUnconnected();

  void SquashFloating(float area_percentage = 0.05f);

  void Resize(size_t width, size_t height);

  void ConnectClosest(size_t tunnel_width = 0);

  [[nodiscard]] const auto& GetMap() const { return map_; }

  static bool IsWall(value_type value) { return value == WallValue; }

 private:
  struct Position {
    Position() = default;
    Position(size_t x, size_t y) : x(x), y(y) {}

    size_t x;
    size_t y;
  };

  static const value_type TemporaryValue;
  static const value_type EmptySpaceValue;
  static const value_type WallValue;

  static size_t CountNeighbours(std::vector<std::vector<value_type>>& states, size_t x, size_t y);

  [[nodiscard]] std::vector<Position> FindRoomEdges(size_t room_index) const;

  void RevertRooms();

  size_t rooms_count_{};
  std::vector<std::vector<value_type>> map_;
};

template <typename T>
size_t FloodFill(std::vector<std::vector<T>>& map, size_t x, size_t y, T new_state) {

  auto prev_state = map[x][y];
  size_t flooded = 1;
  map[x][y] = new_state;
  if (x > 0 && map[x - 1][y] == prev_state) {
    flooded += FloodFill(map, x - 1, y, new_state);
  }

  if (y > 0 && map[x][y - 1] == prev_state) {
    flooded += FloodFill(map, x, y - 1, new_state);
  }

  if (x + 1 < map.size() && map[x + 1][y] == prev_state) {
    flooded += FloodFill(map, x + 1, y, new_state);
  }

  if (x + 1 < map.back().size() && map[x][y + 1] == prev_state) {
    flooded += FloodFill(map, x, y + 1, new_state);
  }
  return flooded;
}

#endif //ANTS_WORLD_MAPGENERATOR_H_
