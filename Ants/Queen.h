//
// Created by Artem Novikov on 03.09.2022.
//

#ifndef ANTS_ANTS_QUEEN_H_
#define ANTS_ANTS_QUEEN_H_

#include "Ant.h"

class Queen : public Ant {
 public:
  Queen(const Vector2f& position, size_t colony_index, GeneralData& general_data, float pheromone_initial)
      : Ant(position, general_data, pheromone_initial) {
    ant_state_ = std::make_unique<FoodSearchState>(sensor_data_, pheromone_data_, movement_data_, general_data_);  /// TODO
  }
 private:
};

#endif //ANTS_ANTS_QUEEN_H_
