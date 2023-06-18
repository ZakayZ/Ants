//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_VCREATUREMAP_H_
#define ANTS_NEW_WORLD_VCREATUREMAP_H_

#include "DataTypes.h"
#include "BoundaryBox.h"

class Creature;
class CreatureList;
class World;


class VCreatureMap {
 public:
  virtual CreatureList GetCreatures(const BoundaryBox<Float, 2>& box) = 0;

  virtual void Update(World& world, Time dt) = 0;

  virtual void AddCreature(Creature* creature_ptr) = 0;

  virtual ~VCreatureMap() = default;
};

#endif //ANTS_NEW_WORLD_VCREATUREMAP_H_
