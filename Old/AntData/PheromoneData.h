//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_ANTDATA_PHEROMONEDATA_H_
#define ANTS_ANTDATA_PHEROMONEDATA_H_

struct PheromoneData {
  explicit PheromoneData(float pheromone) : pheromone_strength(pheromone) {}
  float pheromone_strength;
};

#endif //ANTS_ANTDATA_PHEROMONEDATA_H_
