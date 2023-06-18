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

  PheromoneGland(Float initial_strength, Time effective_time, PheromoneType type);

  [[nodiscard]] PheromoneType GetPheromoneType() const { return type_; }

  [[nodiscard]] Float Secrete(Time dt);

  void SetPheromoneType(PheromoneType type);

  void Reset(Float strength = 1.);

 private:
  Float pheromone_strength_;
  Time effective_time_;
  PheromoneType type_;
};

#endif //ANTS_NEW_CREATURE_ANT_ANTDATA_PHEROMONEGLAND_H_
