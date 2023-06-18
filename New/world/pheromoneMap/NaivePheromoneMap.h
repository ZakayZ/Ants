//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_PHEROMONEMAP_NAIVEPHEROMONEMAP_H_
#define ANTS_NEW_WORLD_PHEROMONEMAP_NAIVEPHEROMONEMAP_H_

#include <vector>

#include "VPheromoneMap.h"

class NaivePheromoneMap : public VPheromoneMap {
 public:
  NaivePheromoneMap(Vector2i dimensions, Vector2f scale = {1., 1.}, Float diffusion_rate = 0., Float evaporation_rate = 0.05);

  PheromoneList GetPheromone(const BoundaryBox<Float, 2>& box, PheromoneType type) override;

  Float GetPheromone(size_t colony_id, size_t x, size_t y, PheromoneType type) const;

  void AddPheromone(const Vector<Float, 2>& position, Float strength, PheromoneType type) override;

  PheromoneData GetPheromoneStrength(const BoundaryBox<Float, 2>& box, PheromoneType type) override;

  void Update(Time dt) override;

 private:
  struct PheromoneTile {
    Vector<float, kPheromoneSize> pheromone{};
    Time last_update_;
  };

  using PheromoneTiles = std::vector<std::vector<PheromoneTile>>;

  friend class PheromoneList;

  [[nodiscard]] Vector2i ToMap(const Position & position) const;

  PheromoneTiles tiles_;
  Vector2f scale_;
  Float diffusion_rate_;
  Float evaporation_rate_;
};

class PheromoneList {
 private:
  class PheromoneIterator;

 public:
  using iterator = PheromoneIterator;

  PheromoneList(NaivePheromoneMap::PheromoneTiles& data, Vector2i l, Vector2i r)
      : data_(data), left_border_(l), right_border_(r) {}

  iterator begin() { return {left_border_[0], left_border_[1], left_border_[0], right_border_[0], data_}; }

  iterator end() { return {right_border_[0], right_border_[1], left_border_[0], right_border_[0], data_}; }

 private:
  class PheromoneIterator {
   public:
    using difference_type = size_t;

    using value_type = NaivePheromoneMap::PheromoneTile;

    using reference = NaivePheromoneMap::PheromoneTile&;

    using pointer = NaivePheromoneMap::PheromoneTile*;

    using iterator_category = typename std::forward_iterator_tag;

    PheromoneIterator(int row, int column, int reset_row, int max_row, NaivePheromoneMap::PheromoneTiles& data)
        : row_(row), column_(column), reset_row_(reset_row), max_row_(max_row), data_(data) {}

    pointer operator->() const {
      return &data_[row_][column_];
    }

    reference operator*() const {
      return data_[row_][column_];
    }

    PheromoneIterator& operator++() {
      ++row_;
      if (row_ >= max_row_) {
        row_ = reset_row_;
        ++column_;
      }
      return *this;
    }

    PheromoneIterator operator++(int) {
      auto copy = *this;
      this->operator++();
      return copy;
    }

    bool operator==(const PheromoneIterator& other) const {
      return row_ == other.row_ && column_ == other.column_;
    }

    bool operator!=(const PheromoneIterator& other) const {
      return row_ != other.row_ || column_ != other.column_;
    }

   private:
    int row_;
    int column_;
    int reset_row_;
    int max_row_;
    NaivePheromoneMap::PheromoneTiles& data_;
  };

  NaivePheromoneMap::PheromoneTiles& data_;
  Vector2i left_border_;
  Vector2i right_border_;
};

#endif //ANTS_NEW_WORLD_PHEROMONEMAP_NAIVEPHEROMONEMAP_H_
