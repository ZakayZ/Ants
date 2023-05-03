//
// Created by Artem Novikov on 03.09.2022.
//

#ifndef ANTS_ANTS_SOLDIER_H_
#define ANTS_ANTS_SOLDIER_H_

#include "Ant.h"

class Soldier : public Ant {
 public:
  Soldier(const Vector2f& position, GeneralData& general_data)
      : Ant(position, general_data) {
    ChangeState<EnemySearchState>();
  }
 private:
};

#endif //ANTS_ANTS_SOLDIER_H_
