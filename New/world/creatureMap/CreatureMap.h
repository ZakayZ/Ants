//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_CREATUREMAP_H_
#define ANTS_NEW_WORLD_CREATUREMAP_H_

#include "VCreatureMap.h"

class CreatureMap;  // TODO

using CreatureMap = CreatureMap;

static_assert(std::is_base_of_v<VCreatureMap, CreatureMap>, "invalid creature map class");

#endif //ANTS_NEW_WORLD_CREATUREMAP_H_
