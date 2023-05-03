//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_HIVE_HIVE_H_
#define ANTS_NEW_HIVE_HIVE_H_

#include "DataTypes.h"

class Hive {  // TODO add colony info
 public:
  Hive(Position position, uint32_t food_cnt);

  [[nodiscard]] const Position& GetPosition() const { return position_; }

  void StoreFood(uint32_t food_stored);

 private:
  Position position_;
  uint32_t food_cnt_;
};

#endif //ANTS_NEW_HIVE_HIVE_H_
