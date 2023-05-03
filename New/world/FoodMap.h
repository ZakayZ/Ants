//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_FOODMAP_H_
#define ANTS_NEW_WORLD_FOODMAP_H_

#include "VFoodMap.h"

class FoodMap;  // TODO

using FoodMap = FoodMap;

static_assert(std::is_base_of_v<VFoodMap, FoodMap>, "invalid food map class");

#endif //ANTS_NEW_WORLD_FOODMAP_H_
