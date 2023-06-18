//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_CREATUREMAP_NAIVECREATUREMAP_H_
#define ANTS_NEW_WORLD_CREATUREMAP_NAIVECREATUREMAP_H_

#include <list>

#include "VCreatureMap.h"
#include "utils/ConditionalIterator.h"

class Creature;

class NaiveCreatureMap : public VCreatureMap {
 private:
  friend class CreatureList;

  using Container = std::list<std::shared_ptr<Creature>>;

 public:
  NaiveCreatureMap() = default;

  Container::iterator begin() { return creatures_.begin(); }

  Container::iterator end() { return creatures_.end(); }

  Container::const_iterator begin() const { return creatures_.begin(); }

  Container::const_iterator end() const { return creatures_.end(); }

  CreatureList GetCreatures(const BoundaryBox<Float, 2>& box) override;

  void Update(World& world, Time dt) override;

  void AddCreature(Creature* creature_ptr) override;

  void AddCreature(const std::shared_ptr<Creature>& creature_ptr);

 private:
  Container creatures_;
};

class CreatureList {
 private:
  class PositionPredicate;

  using BaseIterator = NaiveCreatureMap::Container::iterator;

  using ConstBaseIterator = NaiveCreatureMap::Container::const_iterator;

 public:
  using iterator = ConditionalIterator<BaseIterator, PositionPredicate>;

  using const_iterator = ConditionalIterator<ConstBaseIterator, PositionPredicate>;

  CreatureList(BaseIterator begin, BaseIterator end, const BoundaryBox<Float, 2>& box)
      : begin_(begin, end, PositionPredicate(box)), end_(end, end, PositionPredicate(box)) {}

  iterator begin() { return begin_; }

  iterator end() { return end_; }

 private:
  class PositionPredicate {
   public:
    PositionPredicate(const BoundaryBox<Float, 2>& box) : box_(box) {}

    PositionPredicate(BoundaryBox<Float, 2>&& box) noexcept: box_(std::move(box)) {}

    bool operator()(const std::shared_ptr<Creature>& creature_ptr);

   private:
    BoundaryBox<Float, 2> box_;
  };

  iterator begin_;
  iterator end_;
};

#endif //ANTS_NEW_WORLD_CREATUREMAP_NAIVECREATUREMAP_H_
