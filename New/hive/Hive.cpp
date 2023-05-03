//
// Created by Artem Novikov on 03.05.2023.
//

#include "Hive.h"

Hive::Hive(Position position, uint32_t food_cnt) : position_(position), food_cnt_(food_cnt) {}

void Hive::StoreFood(uint32_t food_stored) {  // TODO thread safety
  food_cnt_ += food_stored;
}