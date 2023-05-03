//
// Created by Artem Novikov on 03.09.2022.
//

#ifndef ANTS_ANTS_SCOUT_H_
#define ANTS_ANTS_SCOUT_H_

#include "Ant.h"

class Scout : public Ant {
 public:
  Scout(const Vector2f& position, GeneralData& general_data)
      : Ant(position, general_data) {
    ChangeState<ScoutingState>();
  }
 private:
};

#endif //ANTS_ANTS_SCOUT_H_
