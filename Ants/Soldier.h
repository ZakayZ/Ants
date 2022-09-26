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
    ant_state_ = std::make_unique<EnemySearchState>(sensor_data_, pheromone_data_, movement_data_, general_data_);
  }
 private:
};

#endif //ANTS_ANTS_SOLDIER_H_
