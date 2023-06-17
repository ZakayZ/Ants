//
// Created by Artem Novikov on 09.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_STATE_STATETYPE_H_
#define ANTS_NEW_CREATURE_ANT_STATE_STATETYPE_H_

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


#endif //ANTS_NEW_CREATURE_ANT_STATE_STATETYPE_H_
