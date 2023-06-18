//
// Created by Artem Novikov on 25.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_H_
#define ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_H_

#include "../State.h"
#include "StateType.h"
#include "creature/ant/antData/GeneralData.h"
#include "creature/ant/antData/PheromoneType.h"

class Ant;

class AntState : public State {
 public:
  AntState(Ant& host);

  virtual void Decide(World& world, Time dt) = 0;

  [[nodiscard]] virtual StateType GetType() const { return StateType::None; }

  Ant& GetHost() { return host_; }

 protected:
  void Rotate();

  void FollowPoint(const Vector2f& point);

  void FollowPheromone(World& world, PheromoneType type, Time dt);

  Ant& host_;
};

#endif //ANTS_NEW_CREATURE_AI_STATE_ANTSTATE_H_
