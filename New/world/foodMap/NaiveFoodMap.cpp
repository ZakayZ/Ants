//
// Created by Artem Novikov on 03.05.2023.
//

#include "NaiveFoodMap.h"

NaiveFoodMap::NaiveFoodMap(const std::vector<FoodSource>& food) : food_(food) {}

NaiveFoodMap::NaiveFoodMap(std::vector<FoodSource>&& food) : food_(std::move(food)) {}

FoodList NaiveFoodMap::GetFoodList(const BoundaryBox<Float, 2>& box) {
  return {food_.begin(), food_.end(), box};
}

void NaiveFoodMap::Update(Time) {}
