//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_HIVE_HIVE_H_
#define ANTS_NEW_HIVE_HIVE_H_

#include "DataTypes.h"

class Hive {  // TODO add colony info
 public:
  Hive(Position position, uint32_t food_cnt, Float size);

  [[nodiscard]] const Position& GetPosition() const { return position_; }

  [[nodiscard]] Float GetSize() const { return size_; }

  [[nodiscard]] bool IsClose(const Position& agent_position) const;

  void StoreFood(uint32_t food_stored);

 private:
  friend class Colony;

  Position position_;
  uint32_t food_cnt_;
  Float size_;
};

#endif //ANTS_NEW_HIVE_HIVE_H_
