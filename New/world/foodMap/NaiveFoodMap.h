//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_FOODMAP_NAIVEFOODMAP_H_
#define ANTS_NEW_WORLD_FOODMAP_NAIVEFOODMAP_H_

#include <vector>

#include "VFoodMap.h"
#include "food/FoodSource.h"
#include "utils/ConditionalIterator.h"

class NaiveFoodMap : public VFoodMap {
 public:
  NaiveFoodMap(const std::vector<FoodSource>& food);

  NaiveFoodMap(std::vector<FoodSource>&& food);

  FoodList GetFoodList(const BoundaryBox<Float, 2>& box) override;

  void Update(Time dt) override;

 private:
  std::vector<FoodSource> food_;
};

class FoodList {
 private:
  class PositionPredicate;

  using BaseIterator = std::vector<FoodSource>::iterator;

  using ConstBaseIterator = std::vector<FoodSource>::const_iterator;

 public:
  using iterator = ConditionalIterator<BaseIterator, PositionPredicate>;

  using const_iterator = ConditionalIterator<ConstBaseIterator, PositionPredicate>;

  FoodList(BaseIterator begin, BaseIterator end, const BoundaryBox<Float, 2>& box)
      : begin_(begin, end, PositionPredicate(box)), end_(end, end, PositionPredicate(box)) {}

  iterator begin() { return begin_; }

  iterator end() { return end_; }

 private:
  class PositionPredicate {
   public:
    PositionPredicate(const BoundaryBox<Float, 2>& box) : box_(box) {}

    PositionPredicate(BoundaryBox<Float, 2>&& box) noexcept: box_(std::move(box)) {}

    inline bool operator()(const FoodSource& food) { return box_.Contains(food.GetPosition()); }

   private:
    BoundaryBox<Float, 2> box_;
  };

  iterator begin_;
  iterator end_;
};

#endif //ANTS_NEW_WORLD_FOODMAP_NAIVEFOODMAP_H_
