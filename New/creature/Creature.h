//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_CREATURE_CREATURE_H_
#define ANTS_NEW_CREATURE_CREATURE_H_

#include <memory>

#include "CreatureData.h"
#include "MoveData.h"
#include "CreatureType.h"

class World;
class AI;

class Creature {
 public:
  Creature(MoveData move_data, CreatureData creature_data, std::unique_ptr<AI>&& brain)
      : move_data_(move_data), creature_data_(creature_data), brain_(std::move(brain)) {}
//  virtual void Move(World& world, Time dt) = 0;
//
//  virtual void Decide(World& world, Time dt) = 0;

  virtual void Update(World& world, Time dt) = 0;

  [[nodiscard]] const Position& GetPosition() const { return move_data_.position; }

  [[nodiscard]] bool Alive() const { return creature_data_.alive; }

  MoveData& GetMoveData() { return move_data_; }

  CreatureData& GetCreatureData() { return creature_data_; }

  AI& GetAI() { return *brain_; }

  [[nodiscard]] CreatureType GetType() const { return type_; }

  virtual ~Creature() = default;

 protected:
  MoveData move_data_;

  CreatureData creature_data_;

  std::unique_ptr<AI> brain_;

  CreatureType type_;
};

#endif //ANTS_NEW_CREATURE_CREATURE_H_
