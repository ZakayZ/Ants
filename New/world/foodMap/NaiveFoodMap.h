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
 private:
  friend class FoodList;

  using Container = std::vector<FoodSource>;

 public:
  NaiveFoodMap(const std::vector<FoodSource>& food);

  NaiveFoodMap(std::vector<FoodSource>&& food);

  Container::iterator begin() { return food_.begin(); }

  Container::iterator end() { return food_.end(); }

  Container::const_iterator begin() const { return food_.begin(); }

  Container::const_iterator end() const { return food_.end(); }

  FoodList GetFoodList(const BoundaryBox<Float, 2>& box) override;

  void Update(Time dt) override;

 private:
  Container food_;
};

class FoodList {
 private:
  class PositionPredicate;

  using BaseIterator = NaiveFoodMap::Container::iterator;

  using ConstBaseIterator = NaiveFoodMap::Container::const_iterator;

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
