//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_HIVEMAP_NAIVEHIVEMAP_H_
#define ANTS_NEW_WORLD_HIVEMAP_NAIVEHIVEMAP_H_

#include <vector>

#include "VHiveMap.h"
#include "colony/Hive.h"
#include "utils/ConditionalIterator.h"

class NaiveHiveMap : public VHiveMap {
 private:
  friend class HiveList;

  using Container = std::vector<Hive>;

 public:
  NaiveHiveMap(const std::vector<Hive>& hives);

  NaiveHiveMap(std::vector<Hive>&& hives) noexcept;

  Container::iterator begin() { return hives_.begin(); }

  Container::iterator end() { return hives_.end(); }

  Container::const_iterator begin() const { return hives_.begin(); }

  Container::const_iterator end() const { return hives_.end(); }

  HiveList GetHiveList(const BoundaryBox<Float, 2>& box) override;

  void Update(Time dt) override;

 private:
  Container hives_;
};

class HiveList {
 private:
  class PositionPredicate;

  using BaseIterator = NaiveHiveMap::Container::iterator;

  using ConstBaseIterator = NaiveHiveMap::Container::const_iterator;

 public:
  using iterator = ConditionalIterator<BaseIterator, PositionPredicate>;

  using const_iterator = ConditionalIterator<ConstBaseIterator, PositionPredicate>;

  HiveList(BaseIterator begin, BaseIterator end, const BoundaryBox<Float, 2>& box)
      : begin_(begin, end, PositionPredicate(box)), end_(end, end, PositionPredicate(box)) {}

  iterator begin() { return begin_; }

  iterator end() { return end_; }

 private:
  class PositionPredicate {
   public:
    PositionPredicate(const BoundaryBox<Float, 2>& box) : box_(box) {}

    PositionPredicate(BoundaryBox<Float, 2>&& box) noexcept: box_(std::move(box)) {}

    inline bool operator()(const Hive& hive) { return box_.Contains(hive.GetPosition()); }

   private:
    BoundaryBox<Float, 2> box_;
  };

  iterator begin_;
  iterator end_;
};

#endif //ANTS_NEW_WORLD_HIVEMAP_NAIVEHIVEMAP_H_
