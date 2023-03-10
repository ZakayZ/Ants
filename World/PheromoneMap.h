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

  PheromoneMap(Vector2i dimensions, float evaporation_rate = 0.05);

  void Update(float delta_time);

  void UpdateTile(int x, int y, float delta_time);

  [[nodiscard]] float GetPheromone(int x, int y, PheromoneType type) const;

  [[nodiscard]] float GetPheromone(const Vector2f& position, PheromoneType type) const;

  [[nodiscard]] PheromoneInfo GetPheromoneCenter(
      const Vector2f& position, float side_length, PheromoneType type) const;

  [[nodiscard]] size_t GetWidth() const { return pheromone_map_.size() - 2; }

  [[nodiscard]] size_t GetHeight() const { return pheromone_map_.back().size() - 2; }

  void LayPheromone(const Vector2f& position, float added_pheromone, PheromoneType type);

 private:
  void ForceUpdateTile(PheromoneTile& tile) const;

  void UpdateTile(PheromoneTile& tile) const;

  mutable std::vector<std::vector<PheromoneTile>> pheromone_map_;
  float evaporation_rate_;
};

#endif //ANTS__PHEROMONEMAP_H_
