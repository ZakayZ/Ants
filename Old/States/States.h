//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_STATES_STATES_H_
#define ANTS_STATES_STATES_H_

enum class StateType {
  None,
  FoodSearch,
  HomeSearch,
  RepellentPheromone,
  AlertColony,
  EnemySearch,
  AttackEnemy,
  Defending,
  Scouting,
  Laying,
  Idle,
};

#endif //ANTS_STATES_STATES_H_
