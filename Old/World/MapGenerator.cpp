//
// Created by Artem Novikov on 04.11.2022.
//

#include "MapGenerator.h"
#include <queue>
#include <unordered_map>
#include <array>

const MapGenerator::value_type MapGenerator::WallValue = UINT32_MAX;

const MapGenerator::value_type MapGenerator::EmptySpaceValue = UINT32_MAX - 1;

const MapGenerator::value_type MapGenerator::TemporaryValue = UINT32_MAX - 2;

MapGenerator::MapGenerator(const std::vector<std::vector<value_type>>& initial_states) : map_(initial_states) {}

MapGenerator::MapGenerator(size_t width, size_t height)
    : rooms_count_(), map_(width, std::vector<value_type>(height, WallValue)) {}

void MapGenerator::Generate(float density, uint32_t seed) {
  rooms_count_ = 0;
  std::srand(seed);
  auto cap = static_cast<int>(density * static_cast<float>(RAND_MAX));
  for (auto& row : map_) {
    for (auto& cell : row) {
      cell = (std::rand() > cap) ? EmptySpaceValue : WallValue;
    }
  }
  for (auto& row : map_) {
    row[0] = row.back() = WallValue;
  }
  for (int i = 0; i < map_.back().size(); ++i) {
    map_[0][i] = map_.back()[i] = WallValue;
  }
}

void MapGenerator::IterateMap(size_t iterations, size_t alive_threshold, size_t revive_threshold) {
  auto next_map = map_;
  for (size_t iter = 0; iter < iterations; ++iter) {
    for (size_t x = 0; x < map_.size(); ++x) {
      for (size_t y = 0; y < map_[x].size(); ++y) {
        auto neighbours_count = CountNeighbours(map_, x, y);
        if (IsWall(next_map[x][y]) && neighbours_count < alive_threshold) {
          next_map[x][y] = EmptySpaceValue;
        } else if (!IsWall(next_map[x][y]) && neighbours_count > revive_threshold) {
          next_map[x][y] = WallValue;
        }
      }
    }
    std::swap(map_, next_map);
  }
}

void MapGenerator::IdentifyRooms() {
  RevertRooms();
  for (size_t x = 0; x < map_.size(); ++x) {
    for (size_t y = 0; y < map_[x].size(); ++y) {
      if (map_[x][y] == EmptySpaceValue) {
        FloodFill<value_type>(map_, x, y, rooms_count_++);
      }
    }
  }
}

void MapGenerator::FillUnconnected() {
  if (rooms_count_ == 0) {
    IdentifyRooms();
  }
  std::vector<size_t> rooms_area(rooms_count_, 0);
  for (auto& row : map_) {
    for (auto val : row) {
      if (!IsWall(val)) {
        ++rooms_area[val];
      }
    }
  }
  size_t max_idx = std::max_element(rooms_area.begin(), rooms_area.end()) - rooms_area.begin();
  for (auto& row : map_) {
    for (auto& val : row) {
      if (val != max_idx) {
        val = WallValue;
      }
    }
  }
}

void MapGenerator::SquashFloating(float area_percentage) {
  const auto area_threshold = static_cast<size_t>(area_percentage * float(map_.size() * map_.back().size()));
  for (size_t x = 0; x < map_.size(); ++x) {
    for (size_t y = 0; y < map_[x].size(); ++y) {
      if (map_[x][y] == WallValue) {
        auto area = FloodFill(map_, x, y, TemporaryValue);
        if (area < area_threshold) {
          FloodFill(map_, x, y, EmptySpaceValue);
        }
      }
    }
  }
  /// return walls
  for (size_t x = 0; x < map_.size(); ++x) {
    for (size_t y = 0; y < map_[x].size(); ++y) {
      if (map_[x][y] == TemporaryValue) {
        FloodFill(map_, x, y, WallValue);
      }
    }
  }
}

void MapGenerator::ConnectClosest(size_t tunnel_width) {
  struct CellData { Position parent_position; size_t dist; };
  if (rooms_count_ == 0) { IdentifyRooms(); }
  auto Hash = [width = map_.size()](const Position& position) { return position.x + position.y * width; };
  if (rooms_count_ <= 1) { return; }
  for (size_t current_room = rooms_count_ - 1; current_room > 0; --current_room) {
    auto room_edges = FindRoomEdges(current_room);
    std::queue<Position> new_layer;
    std::unordered_map<size_t, CellData> cell_data;
    for (auto& position : room_edges) {
      new_layer.push(position);
      cell_data.emplace(Hash(position), CellData{position, 0});
    }
    Position closest_room_position(map_.size(), map_.back().size());
    while (!new_layer.empty()) {
      auto position = new_layer.front();
      new_layer.pop();
      auto new_dist = cell_data[Hash(position)].dist + 1;
      std::array<Position, 4> new_cells = {Position(position.x - 1, position.y), Position(position.x + 1, position.y),
                                           Position(position.x, position.y - 1), Position(position.x, position.y + 1)};
      for (const auto& new_position : new_cells) {
        auto hash = Hash(new_position);
        if (new_position.x < map_.size() - 1 && new_position.y < map_.back().size() - 1
            && map_[new_position.x][new_position.y] != current_room && !cell_data.contains(hash)) {
          cell_data.emplace(hash, CellData{position, new_dist});
          if (map_[new_position.x][new_position.y] == WallValue) {
            new_layer.push(new_position);
          } else {
            closest_room_position = new_position;
            goto EndLoop;
          }
        }
      }
    }
    EndLoop:
    if (closest_room_position.x == map_.size() || closest_room_position.y == map_.back().size()) {
      throw std::runtime_error("invalid map");
    }
    auto new_room_number = map_[closest_room_position.x][closest_room_position.y];
    FloodFill(map_, room_edges.back().x, room_edges.back().y, new_room_number);
    auto cell = closest_room_position;
    while (cell_data[Hash(cell)].dist > 0) {
      for (size_t x = cell.x - std::min(tunnel_width, cell.x); x < std::min(map_.size(), cell.x + tunnel_width + 1);
           ++x) {
        for (size_t y = cell.y - std::min(tunnel_width, cell.y);
             y < std::min(map_[x].size(), cell.y + tunnel_width + 1); ++y) {
          map_[x][y] = new_room_number;
        }
      }
      cell = cell_data[Hash(cell)].parent_position;
    }
  }
}

void MapGenerator::Resize(size_t width, size_t height) {
  std::vector<std::vector<value_type>> map(width, std::vector<value_type>(height));
  auto scale_x = float(width) / float(map_.size());
  auto scale_y = float(height) / float(map_.back().size());
  for (size_t x = 0; x < map.size(); ++x) {
    for (size_t y = 0; y < map[x].size(); ++y) {
      map[x][y] = map_[size_t(float(x) / scale_x)][size_t(float(y) / scale_y)];
    }
  }
  map_ = std::move(map);
}

size_t MapGenerator::CountNeighbours(std::vector<std::vector<value_type>>& states, size_t x, size_t y) {
  size_t count = 0;
  for (ssize_t i = -1; i < 2; ++i) {
    if (x + i < 0 || x + i >= states.size()) {
      count += 3;
      continue;
    }
    for (ssize_t j = -1; j < 2; ++j) {
      if (y + j < 0 || y + j >= states.back().size()) {
        ++count;
        continue;
      }
      count += IsWall(states[x + i][y + j]);
    }
  }
  count -= IsWall(states[x][y]);
  return count;
}

std::vector<MapGenerator::Position> MapGenerator::FindRoomEdges(size_t room_index) const {
  std::vector<Position> edge_tiles;
  for (size_t x = 0; x < map_.size(); ++x) {
    for (size_t y = 0; y < map_[x].size(); ++y) {
      if (map_[x][y] == room_index && ((x > 0 && map_[x - 1][y] == WallValue) ||
          (y > 0 && map_[x][y - 1] == WallValue) ||
          (x + 1 < map_.size() && map_[x + 1][y] == WallValue) ||
          (y + 1 < map_[x].size() && map_[x][y + 1] == WallValue))) {
        edge_tiles.emplace_back(x, y);
      }
    }
  }
  return edge_tiles;
}
void MapGenerator::RevertRooms() {
  for (auto& row : map_) {
    for (auto& cell : row) {
      if (cell != WallValue) {
        cell = EmptySpaceValue;
      }
    }
  }
  rooms_count_ = 0;
}
