//
// Created by Artem Novikov on 03.05.2023.
//

#include "Hive.h"

Hive::Hive(Position position, uint32_t food_cnt, Float size) : position_(position), food_cnt_(food_cnt), size_(size) {}

void Hive::StoreFood(uint32_t food_stored) {  // TODO thread safety
  food_cnt_ += food_stored;
}

bool Hive::IsClose(const Position& agent_position) const {
  return (agent_position - position_).SquaredLength() <= std::pow(size_, 2);
}
