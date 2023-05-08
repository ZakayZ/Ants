//
// Created by Artem Novikov on 06.05.2023.
//

#ifndef ANTS_NEW_WORLD_OBJECTMAP_NAIVEOBJECTMAP_H_
#define ANTS_NEW_WORLD_OBJECTMAP_NAIVEOBJECTMAP_H_

#include "VObjectMap.h"

class NaiveObjectMap : public VObjectMap {
 public:
  NaiveObjectMap(Vector2i dimensions, Vector2f scale);

  bool Empty(const Position& position) override;

  WallInfo WallDistances(const Position& position) override;

  std::optional<Position> RayCast(const Position& start, const Position& end) override;

  bool Visible(const Position& observer, const Position& object) override;

  std::vector<Position> FindPath(const Position& start, const Position& end) override;

  void Update(Time dt) override;

 private:
  Vector2i ToMap(const Position& position) const;

  bool Empty(Vector2i position);

  std::vector<std::vector<bool>> map_;
  Vector2<Float> scale_;
};

#endif //ANTS_NEW_WORLD_OBJECTMAP_NAIVEOBJECTMAP_H_
