//
// Created by Artem Novikov on 03.05.2023.
//

#include "NaiveCreatureMap.h"
#include "world/World.h"
#include "creature/Creature.h"

CreatureList NaiveCreatureMap::GetCreatures(const BoundaryBox<Float, 2>& box) {
  return {creatures_.begin(), creatures_.end(), box};
}

void NaiveCreatureMap::Update(World& world, Time dt) {
  for (auto& creature_ptr : creatures_) {
    creature_ptr->Update(world, dt);
  }

  for (auto it = creatures_.begin(); it != creatures_.end(); ++it) {
    if (!(*it)->Alive()) {
      creatures_.erase(it++);
    }
  }
}