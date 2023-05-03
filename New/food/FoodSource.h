//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_FOOD_FOODSOURCE_H_
#define ANTS_NEW_FOOD_FOODSOURCE_H_

#include "DataTypes.h"

class FoodSource {
 public:
  FoodSource(Position position, uint32_t food_cnt);

  [[nodiscard]] const Position& GetPosition() const { return position_; }

  uint32_t GetFood(uint32_t food_requested);

  [[nodiscard]] bool Empty() const { return food_cnt_ == 0; }

 private:
  Position position_;
  uint32_t food_cnt_;
};

#endif //ANTS_NEW_FOOD_FOODSOURCE_H_
