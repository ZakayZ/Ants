//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS__REQUIREMENTS_H_
#define ANTS__REQUIREMENTS_H_

#include <typeinfo>

using RequireType = uint8_t;

static const RequireType RequireFood = 1 << 0;

static const RequireType RequireFoodStorage = 1 << 1;

static const RequireType RequireHome = 1 << 2;

static const RequireType RequireHiveStorage = 1 << 3;

static const RequireType RequirePheromone = 1 << 4;

static const RequireType RequireAnt = 1 << 5;

#endif //ANTS__REQUIREMENTS_H_
