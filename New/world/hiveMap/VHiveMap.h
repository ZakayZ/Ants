//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_VHIVEMAP_H_
#define ANTS_NEW_WORLD_VHIVEMAP_H_

#include "DataTypes.h"
#include "BoundaryBox.h"

class HiveList;

class VHiveMap {
 public:
  virtual HiveList GetHiveList(const BoundaryBox<Float, 2>& box) = 0;

  virtual void Update(Time dt) = 0;

  virtual ~VHiveMap() = default;
};

#endif //ANTS_NEW_WORLD_VHIVEMAP_H_
