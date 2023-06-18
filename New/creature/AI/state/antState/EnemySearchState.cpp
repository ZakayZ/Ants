//
// Created by Artem Novikov on 26.05.2023.
//

#include "EnemySearchState.h"

#include "creature/ant/Ant.h"
#include "world/World.h"

const Time EnemySearchState::ScanDelay = 0.5;

void EnemySearchState::Decide(World& world, Time dt) {
  scan_cooldown_.Update(dt);

  host_.LayPheromone(world, dt);
  FollowPheromone(world, PheromoneType::Enemy, dt);

  if (scan_cooldown_.Ready()) {
    scan_cooldown_.Use();

    if (enemy_.expired()) {
      FindEnemy(world);
    }

    if (enemy_.expired()) {
      return;
    }

    auto enemy_ptr = enemy_.lock();
    if ((enemy_ptr->GetPosition() - host_.GetPosition()).SquaredLength()
        <= std::pow(2 * host_.GetGeneralData().ant_size, 2)) {
      host_.GetStateManager().CreatureInteraction(enemy_ptr);
      return;
    }

    FollowPoint(enemy_ptr->GetPosition());
  }
}

void EnemySearchState::FindEnemy(World& world) {
  enemy_.reset();
  for (auto& creature_ptr : world.GetCreatureMap().GetCreatures(host_.VisibleRange())) {
    if (creature_ptr->GetType() == CreatureType::Ant) {
      assert(dynamic_cast<Ant*>(&*creature_ptr) != nullptr);
      if (static_cast<Ant&>(*creature_ptr).GetGeneralData().colony_index != host_.GetGeneralData().colony_index) {
        enemy_ = creature_ptr;
        break;
      }
    } else {
      /// TODO creatures
    }
  }
}
