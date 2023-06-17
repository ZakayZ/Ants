//
// Created by Artem Novikov on 02.05.2023.
//

#ifndef ANTS__DATATYPES_H_
#define ANTS__DATATYPES_H_

#include "Vector.h"

using Float = float;
using PrecisionFloat = double;
using Time = float;

using Position = Vector<Float, 2>;
using Velocity = Vector<Float, 2>;

struct PheromoneData {
  Float total_strength;
  Position mean_position;
};

#endif //ANTS__DATATYPES_H_
