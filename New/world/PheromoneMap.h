//
// Created by Artem Novikov on 03.05.2023.
//

#ifndef ANTS_NEW_WORLD_PHEROMONEMAP_H_
#define ANTS_NEW_WORLD_PHEROMONEMAP_H_

#include "VPheromoneMap.h"

class PheromoneMap; // TODO

using PheromoneMap = PheromoneMap;

static_assert(std::is_base_of_v<VPheromoneMap, PheromoneMap>, "invalid pheromone map class");

#endif //ANTS_NEW_WORLD_PHEROMONEMAP_H_
