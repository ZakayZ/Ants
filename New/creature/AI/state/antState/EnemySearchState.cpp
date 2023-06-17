//
// Created by Artem Novikov on 26.05.2023.
//

#include "EnemySearchState.h"

#include "creature/ant/Ant.h"
#include "world/World.h"

const Time EnemySearchState::ScanDelay = 1;

void EnemySearchState::Decide(World& world, Time dt) {
  attack_delay_.Update(dt);

  host_.LayPheromone(dt);
  FollowPheromone(world, PheromoneType::Enemy, dt);

  if (attack_delay_.Ready()) {
    FindEnemy(world);
    if (enemy_ != nullptr) {
      FollowPoint(enemy_->GetPosition());

      if ((enemy_->GetPosition() - host_.GetPosition()).SquaredLength() <= std::pow(2 * general_data_.ant_size, 2)) {
        host_.GetStateManager().CreatureInteraction(*enemy_);
        return;
      }
    }

    attack_delay_.Use();
  }
}

void EnemySearchState::FindEnemy(World& world) {
  enemy_ = nullptr;
  for (auto& creature_ptr : world.GetCreatureMap().GetCreatures(host_.VisibleRange())) {
    if (creature_ptr->GetType() == CreatureType::Ant) {
      if (static_cast<Ant&>(*creature_ptr).GetGeneralData().colony_index != general_data_.colony_index) {  /// TODO maybe shared ptr ant
        enemy_ = creature_ptr.get();
        break;
      }
    } else {
      /// TODO
    }
  }
}
