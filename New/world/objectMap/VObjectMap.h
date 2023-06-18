//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_VOBJECTMAP_H_
#define ANTS_NEW_WORLD_VOBJECTMAP_H_

#include <optional>

#include "DataTypes.h"
#include "BoundaryBox.h"

struct WallInfo {
  Float up;
  Float down;
  Float left;
  Float right;
};

class VObjectMap {
 public:
  virtual bool Empty(const Position& position) const = 0;

  virtual WallInfo WallDistances(const Position& position) = 0;

  virtual std::optional<Position> RayCast(const Position& start, const Position& end) = 0;

  virtual bool Visible(const Position& observer, const Position& object) = 0;

  virtual std::vector<Position> FindPath(const Position& start, const Position& end) = 0;

  virtual void Update(Time dt) = 0;

  virtual ~VObjectMap() = default;
};

#endif //ANTS_NEW_WORLD_VOBJECTMAP_H_
