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
    Vector<float, kPheromoneSize> pheromone{};
    float cumulative_delta_time{};
  };

  PheromoneMap(size_t colonies_number, Vector2i dimensions, float evaporation_rate = 0.05);

  void Update(float delta_time);

  [[nodiscard]] float GetPheromone(size_t colony_index, int x, int y, PheromoneType type) const;

  [[nodiscard]] float GetPheromone(size_t colony_index, const Vector2f& position, PheromoneType type) const;

  [[nodiscard]] PheromoneInfo GetPheromoneCenter(
      size_t colony_index, const Vector2f& position, float side_length, PheromoneType type) const;

  [[nodiscard]] size_t GetWidth() const { return pheromone_map_[0].size() - 2; }

  [[nodiscard]] size_t GetHeight() const { return pheromone_map_[0].back().size() - 2; }

  void LayPheromone(size_t colony_index, const Vector2f& position, float added_pheromone, PheromoneType type);

 private:
  void ForceUpdateTile(PheromoneTile& tile) const;

  void UpdateTile(PheromoneTile& tile) const;

  float evaporation_rate_;
  mutable std::vector<std::vector<std::vector<PheromoneTile>>> pheromone_map_;
};

#endif //ANTS__PHEROMONEMAP_H_
