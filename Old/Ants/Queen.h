//
// Created by Artem Novikov on 03.09.2022.
//

#ifndef ANTS_ANTS_QUEEN_H_
#define ANTS_ANTS_QUEEN_H_

#include "Ant.h"

class Queen : public Ant {
 public:
  Queen(const Vector2f& position, GeneralData& general_data)
      : Ant(position, general_data) {
    ChangeState<LayingState>();
  }
 private:
};

#endif //ANTS_ANTS_QUEEN_H_
