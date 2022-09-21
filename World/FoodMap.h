//
// Created by Artem Novikov on 19.09.2022.
//

#ifndef ANTS_WORLD_FOODMAP_H_
#define ANTS_WORLD_FOODMAP_H_

#include "FoodSource.h"

class FoodMap {
 public:
  using Holder = std::vector<FoodSource>;
  using iterator = Holder::iterator;
  using const_iterator = Holder::const_iterator;

  FoodMap(const std::vector<FoodSource>& food) : food_sources_(food) {}

  void Update(float delta_time) {
    for (auto it = food_sources_.begin(); it != food_sources_.end(); ++it) {
      if (it->IsEmpty()) {
        food_sources_.erase(it);
        break;
      }
    }
  }

  void AddFood(const FoodSource& source) { food_sources_.push_back(source); }

  iterator begin() { return food_sources_.begin(); }

  const_iterator begin() const { return food_sources_.cbegin(); }

  const_iterator cbegin() const { return food_sources_.cbegin(); }

  iterator end() { return food_sources_.end(); }

  const_iterator end() const { return food_sources_.cend(); }

  const_iterator cend() const { return food_sources_.cend(); }

 private:
  std::vector<FoodSource> food_sources_;
};

#endif //ANTS_WORLD_FOODMAP_H_
