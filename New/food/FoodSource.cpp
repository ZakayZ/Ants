//
// Created by Artem Novikov on 03.05.2023.
//

#include "FoodSource.h"

FoodSource::FoodSource(Position position, uint32_t food_cnt, Float size)
    : position_(position), food_cnt_(food_cnt), size_(size) {}

uint32_t FoodSource::GetFood(uint32_t food_requested) { // TODO thread safety
  if (food_requested >= food_cnt_) {
    food_requested = food_cnt_;
  }

  food_cnt_ -= food_requested;

  return food_requested;
}

bool FoodSource::IsClose(const Position& agent_position) const {
  return (agent_position - position_).SquaredLength() <= std::pow(size_, 2);
}
