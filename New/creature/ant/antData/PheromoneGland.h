//
// Created by Artem Novikov on 09.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_ANTDATA_PHEROMONEGLAND_H_
#define ANTS_NEW_CREATURE_ANT_ANTDATA_PHEROMONEGLAND_H_

#include "DataTypes.h"
#include "PheromoneType.h"

class PheromoneGland {
 public:
  PheromoneGland();

  PheromoneGland(Float initial_strength, Time active_time, PheromoneType type);

  [[nodiscard]] PheromoneType GetPheromoneType() const { return type_; }

  [[nodiscard]] Float Secrete(Time dt);

 private:
  Float pheromone_strength_;
  Time active_time_;
  PheromoneType type_;
};

#endif //ANTS_NEW_CREATURE_ANT_ANTDATA_PHEROMONEGLAND_H_
