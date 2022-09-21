//
// Created by Artem Novikov on 27.08.2022.
//

#ifndef ANTS__PHEROMONEMAP_H_
#define ANTS__PHEROMONEMAP_H_

#include <vector>

#include "Vector.h"
#include "PheromoneType.h"

class PheromoneMap {
 public:
  struct PheromoneInfo {
    Vector2f center{};
    float strength{};
  };

  struct PheromoneTile {
    PheromoneTile(size_t colonies_number) : pheromone(colonies_number), cumulative_delta_time(colonies_number) {}

    std::vector<Vector<float, kPheromoneSize>> pheromone;
    std::vector<float> cumulative_delta_time;
  };

  PheromoneMap(Vector2i dimensions, size_t colonies_number, float evaporation_rate = 0.05);

  void Update(float delta_time);

  [[nodiscard]] float GetPheromone(int x, int y, size_t colony_index, PheromoneType type) const;

  [[nodiscard]] float GetPheromone(const Vector2f& position, size_t colony_index, PheromoneType type) const;

  [[nodiscard]] PheromoneInfo GetPheromoneCenter(
      const Vector2f& position, float side_length, size_t colony_index, PheromoneType type) const;

  [[nodiscard]] size_t GetWidth() const { return pheromone_map_.size() - 2; }

  [[nodiscard]] size_t GetHeight() const { return pheromone_map_.back().size() - 2; }

  void LayPheromone(const Vector2f& position, float added_pheromone, size_t colony_index, PheromoneType type);

 private:
  inline void UpdateTileTime(PheromoneTile& tile, float delta_time) const;

  inline void ForceUpdateTile(PheromoneTile& tile) const;

  inline void ForceUpdateTile(PheromoneTile& tile, size_t colony_index) const;

  inline void UpdateTile(PheromoneTile& tile) const;

  inline void UpdateTile(PheromoneTile& tile, size_t colony_index) const;

  float evaporation_rate_;
  mutable std::vector<std::vector<PheromoneTile>> pheromone_map_;
};

#endif //ANTS__PHEROMONEMAP_H_
