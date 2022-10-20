//
// Created by Artem Novikov on 03.09.2022.
//

#ifndef ANTS_ANTS_WORKER_H_
#define ANTS_ANTS_WORKER_H_

#include "Ant.h"

class Worker : public Ant {
 public:
  Worker(const Vector2f& position, GeneralData& general_data)
      : Ant(position, general_data) {
    ChangeState<FoodSearchState>();
  }
 private:
};

#endif //ANTS_ANTS_WORKER_H_
