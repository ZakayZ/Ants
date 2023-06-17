//
// Created by Artem Novikov on 09.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_STATE_FOODSEARCH_H_
#define ANTS_NEW_CREATURE_ANT_STATE_FOODSEARCH_H_

#include "AntState.h"
#include "food/FoodSource.h"

class FoodSearchState : public AntState {
 public:
  FoodSearchState(Ant& host) : AntState(host) {};

  void Decide(World& world, Time dt) override;

  [[nodiscard]] StateType GetType() const override { return StateType::FoodSearch; }

 private:
  void FindFood(World& world);

  FoodSource* food_ = nullptr;
};

#endif //ANTS_NEW_CREATURE_ANT_STATE_FOODSEARCH_H_
