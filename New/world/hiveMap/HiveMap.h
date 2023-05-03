//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_HIVEMAP_H_
#define ANTS_NEW_WORLD_HIVEMAP_H_

#include "VHiveMap.h"
#include "NaiveHiveMap.h"

using HiveMap = NaiveHiveMap;

static_assert(std::is_base_of_v<VHiveMap, HiveMap>, "invalid hive map class");

#endif //ANTS_NEW_WORLD_HIVEMAP_H_
