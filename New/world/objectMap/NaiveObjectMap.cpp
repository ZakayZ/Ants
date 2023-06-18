//
// Created by Artem Novikov on 06.05.2023.
//

#include <unordered_map>
#include <set>

#include "NaiveObjectMap.h"

NaiveObjectMap::NaiveObjectMap(Vector2i dimensions, Vector2f scale)
    : map_(dimensions[0], std::vector<bool>(dimensions[1])), scale_(scale) {}

bool NaiveObjectMap::Empty(const Position& position) const {
  return Empty(ToMap(position));
}

bool NaiveObjectMap::Empty(size_t x, size_t y) const {
  return !map_[x][y];
}


WallInfo NaiveObjectMap::WallDistances(const Position& position) {
  auto pos_int = ToMap(position);
  return {
      .up=map_[pos_int[0]][pos_int[1] + 1] ? Float(pos_int[1] + 1) * scale_[1] - position[1] : MAXFLOAT,
      .down=map_[pos_int[0]][pos_int[1] - 1] ? position[1] - Float(pos_int[1] - 1) * scale_[1] : MAXFLOAT,
      .left=map_[pos_int[0] - 1][pos_int[1]] ? position[0] - Float(pos_int[0] - 1) * scale_[0] : MAXFLOAT,
      .right=map_[pos_int[0] + 1][pos_int[1]] ? Float(pos_int[0] + 1) * scale_[0] - position[0] : MAXFLOAT,
  };
}

std::optional<Position> NaiveObjectMap::RayCast(const Position& start, const Position& end) {
  auto start_int = ToMap(start);
  auto end_int = ToMap(end);
  auto direction = end - start;
//  auto direction = Vector2<Float>(std::abs(end - start));

  Float offset = Float(start_int[0] + 1) * scale_[0] - start[0];
  for (int x = 0; x < end_int[0] - start_int[0]; ++x) {
    auto delta_x = Float(x) * scale_[0] + offset;
    auto delta_y = direction[1] * delta_x / direction[0];
    int y = int(start[1] + delta_y);
    if (!Empty(Vector2i(start_int[0] + x, y))) {
      return Position(start[0] + delta_x, start[1] + delta_y);
    }
  }

  offset = start[0] - Float(start_int[0]) * scale_[0];
  for (int x = 0; x < start_int[0] - end_int[0]; ++x) {
    auto delta_x = Float(-x) * scale_[0] + offset;
    auto delta_y = direction[1] * delta_x / direction[0];
    int y = int(start[1] + delta_y);
    if (!Empty(Vector2i(start_int[0] - x, y))) {
      return Position(start[0] + delta_x, start[1] + delta_y);
    }
  }

  offset = Float(start_int[1] + 1) * scale_[1] - start[1];
  for (int y = 0; y < end_int[1] - start_int[1]; ++y) {
    auto delta_y = Float(y) * scale_[1] + offset;
    auto delta_x = direction[0] * delta_y / direction[1];
    int x = int(start[0] + delta_x);
    if (!Empty(Vector2i(x, start_int[1] + y))) {
      return Position(start[0] + delta_x, start[1] + delta_y);
    }
  }

  offset = start[1] - Float(start_int[1]) * scale_[1];
  for (int y = 0; y < start_int[1] - end_int[1]; ++y) {
    auto delta_y = Float(-y) * scale_[1] + offset;
    auto delta_x = direction[0] * delta_y / direction[1];
    int x = int(start[0] + delta_x);
    if (!Empty(Vector2i(x, start_int[1] - y))) {
      return Position(start[0] + delta_x, start[1] + delta_y);
    }
  }

  return {};
}

bool NaiveObjectMap::Visible(const Position& observer, const Position& object) {
  return !RayCast(observer, object).has_value();
}

/// TODO improve to bidirectional
std::vector<Position> NaiveObjectMap::FindPath(const Position& start, const Position& end) {
  using PathData = std::pair<int, int>; // distance, vertex


  std::unordered_map<int, PathData> visited_data;
  std::set<PathData> closest_data;

  auto start_int = ToMap(start);
  auto end_int = ToMap(end);
  auto start_vertex = start_int[0] + start_int[1] * int(map_.size());
  closest_data.insert({0, start_vertex});
  while (!closest_data.empty()) {
    auto[heuristic_distance, vertex] = *closest_data.begin();
    auto distance = visited_data[vertex].first;
    auto pos = Vector2i(vertex % map_.size(), vertex / map_.size());
    closest_data.erase(closest_data.begin());

    /// up
    int child = vertex + map_.size();
    auto it = visited_data.find(child);
    if (it == visited_data.end() && pos[1] + 1 < map_.back().size() && Empty(Vector2i(pos[0], pos[1] + 1))) {
      closest_data.insert({distance + 1 + std::abs(end_int[0] - pos[0]) + std::abs(end_int[1] - pos[1] - 1), child});
      visited_data[child] = {distance + 1, vertex};
    }

    /// down
    child = vertex - map_.size();
    it = visited_data.find(child);
    if (it == visited_data.end() && pos[1] > 0 && Empty(Vector2i(pos[0], pos[1] - 1))) {
      closest_data.insert({distance + 1 + std::abs(end_int[0] - pos[0]) + std::abs(end_int[1] - pos[1] + 1), child});
      visited_data[child] = {distance + 1, vertex};
    }

    /// left
    child = vertex - 1;
    it = visited_data.find(child);
    if (it == visited_data.end() && pos[0] > 0 && Empty(Vector2i(pos[0] - 1, pos[1]))) {
      closest_data.insert({distance + 1 + std::abs(end_int[0] - pos[0] + 1) + std::abs(end_int[1] - pos[1]), child});
      visited_data[child] = {distance + 1, vertex};
    }

    /// right
    child = vertex + 1;
    it = visited_data.find(child);
    if (it == visited_data.end() && pos[0] + 1 < map_.size() && Empty(Vector2i(pos[0] + 1, pos[1]))) {
      closest_data.insert({distance + 1 + std::abs(end_int[0] - pos[0] - 1) + std::abs(end_int[1] - pos[1]), child});
      visited_data[child] = {distance + 1, vertex};
    }
  }

  /// restore path
  int vertex = end_int[0] + end_int[1] * int(map_.size());
  std::vector<Position> path = {end};
  while (vertex != start_vertex) {
    vertex = visited_data[vertex].first;
    auto pos = Vector2i(vertex % map_.size(), vertex / map_.size());
    path.emplace_back(scale_[0] * (pos[0] + 0.5), scale_[1] * (pos[1] + 0.5));
  }
  std::reverse(path.begin(), path.end());
  return path;
}

void NaiveObjectMap::Update(Time dt) {
  // TODO
}

Vector2i NaiveObjectMap::ToMap(const Position& position) const {
  return {int(position[0] / scale_[0]), int(position[1] / scale_[1])};;
}

bool NaiveObjectMap::Empty(Vector2i position) {
  return !map_[position[0]][position[1]];
}
