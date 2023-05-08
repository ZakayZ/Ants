//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_CREATURE_CREATURE_H_
#define ANTS_NEW_CREATURE_CREATURE_H_

#include "DataTypes.h"

class World;

class Creature {
 public:
  virtual void Move(World& world, Time dt) = 0;

  virtual void Decide(World& world) = 0;

  virtual void Update(World& world, Time dt) = 0;

  [[nodiscard]] const Position& GetPosition() const { return position_; }

  [[nodiscard]] bool Alive() const { return is_alive_; }

  virtual ~Creature() = default;

 protected:
  Position position_;
  bool is_alive_;
};

#endif //ANTS_NEW_CREATURE_CREATURE_H_
