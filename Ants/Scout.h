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
    ant_state_ = std::make_unique<ScoutingState>(sensor_data_, pheromone_data_, movement_data_, general_data_);
  }
 private:
};

#endif //ANTS_ANTS_SCOUT_H_
