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
    ant_state_ = std::make_unique<FoodSearchState>(food_data_, sensor_data_, pheromone_data_, movement_data_, general_data_);
  }
 private:
};

#endif //ANTS_ANTS_WORKER_H_
