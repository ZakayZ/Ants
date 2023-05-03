//
// Created by Artem Novikov on 03.05.2023.
//

#include "NaiveHiveMap.h"

NaiveHiveMap::NaiveHiveMap(const std::vector<Hive>& hives) : hives_(hives) {}

NaiveHiveMap::NaiveHiveMap(std::vector<Hive>&& hives) noexcept: hives_(std::move(hives)) {}

HiveList NaiveHiveMap::GetHiveList(const BoundaryBox<Float, 2>& box) {
  return {hives_.begin(), hives_.end(), box};
}

void NaiveHiveMap::Update(Time) {}
