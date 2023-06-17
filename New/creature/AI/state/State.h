//
// Created by Artem Novikov on 09.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_STATE_STATE_H_
#define ANTS_NEW_CREATURE_ANT_STATE_STATE_H_

#include "DataTypes.h"

class Creature;
class World;

class State {
 public:
  State(Creature& host) : host_(host) {};

  virtual void Decide(World& world, Time dt) = 0;

  virtual ~State() = default;

 protected:
  void ChangeState(std::unique_ptr<State>&& state);

  Creature& host_;
};

#endif //ANTS_NEW_CREATURE_ANT_STATE_STATE_H_
