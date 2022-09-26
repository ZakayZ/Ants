//
// Created by Artem Novikov on 24.09.2022.
//

#ifndef ANTS_ANTDATA_FIGHTDATA_H_
#define ANTS_ANTDATA_FIGHTDATA_H_

struct FightData {
  FightData(int max_health) : health(max_health) {}

  int health;
};

#endif //ANTS_ANTDATA_FIGHTDATA_H_
