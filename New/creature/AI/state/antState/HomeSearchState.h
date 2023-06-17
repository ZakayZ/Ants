//
// Created by Artem Novikov on 25.05.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_STATE_HOMESEARCHSTATE_H_
#define ANTS_NEW_CREATURE_AI_STATE_HOMESEARCHSTATE_H_

#include "AntState.h"
#include "colony/Hive.h"

class HomeSearchState : public AntState {
 public:
  HomeSearchState(Ant& host) : AntState(host) {};

  void Decide(World& world, Time dt) override;

  [[nodiscard]] StateType GetType() const override { return StateType::HomeSearch; }

 private:
  void FindHive(World& world);

  Hive* hive_ = nullptr;
};

#endif //ANTS_NEW_CREATURE_AI_STATE_HOMESEARCHSTATE_H_
