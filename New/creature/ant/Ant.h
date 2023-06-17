//
// Created by Artem Novikov on 08.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_ANT_H_
#define ANTS_NEW_CREATURE_ANT_ANT_H_

#include "creature/Creature.h"
#include "antData/GeneralData.h"
#include "antData/PheromoneGland.h"
#include "creature/AI/state/antState/AntStateManager.h"
#include "utils/Cooldown.h"

#include "food/FoodSource.h"
#include "colony/Hive.h"

#include "BoundaryBox.h"

class Ant : public Creature {
 public:
  Ant(MoveData move_data, CreatureData creature_data, std::unique_ptr<AI>&& brain, const GeneralData& general_data)
      : Creature(move_data, creature_data, std::move(brain)), general_data_(general_data),
        random_walk_(general_data.wander_cooldown) {}

  void Update(World& world, Time dt) override;

  const GeneralData& GetGeneralData() { return general_data_; }

  [[nodiscard]] BoundaryBox2<Float> VisibleRange() const;

  [[nodiscard]] BoundaryBox2<Float> SensitiveRange() const;

  Float LayPheromone(Time dt);

  AntStateManager& GetStateManager() { return static_cast<AntStateManager&>(*brain_); }

 protected:
  void Move(Time dt);

  void AvoidCollision(World& world, Time dt);

  const GeneralData& general_data_;
  PheromoneGland pheromone_gland_{};

  Cooldown random_walk_;
};

#endif //ANTS_NEW_CREATURE_ANT_ANT_H_
