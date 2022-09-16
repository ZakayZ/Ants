//
// Created by Artem Novikov on 27.08.2022.
//

#ifndef ANTS__PHEROMONETYPE_H_
#define ANTS__PHEROMONETYPE_H_

enum PheromoneType {
  Food = 0,
  Home = 1,
  None,
};

static const size_t kPheromoneSize = 2;

#endif //ANTS__PHEROMONETYPE_H_
