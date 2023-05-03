//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_OBJECTMAP_H_
#define ANTS_NEW_WORLD_OBJECTMAP_H_

#include "VObjectMap.h"

class ObjectMap; // TODO

using ObjectMap = ObjectMap;

static_assert(std::is_base_of_v<VObjectMap, ObjectMap>, "invalid hive map class");

#endif //ANTS_NEW_WORLD_OBJECTMAP_H_
