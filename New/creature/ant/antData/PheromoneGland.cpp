//
// Created by Artem Novikov on 09.05.2023.
//

#include "PheromoneGland.h"

PheromoneGland::PheromoneGland() : pheromone_strength_(0), active_time_(1), type_(None) {}

PheromoneGland::PheromoneGland(Float initial_strength, Time active_time, PheromoneType type)
    : pheromone_strength_(initial_strength), active_time_(active_time), type_(type) {}

Float PheromoneGland::Secrete(Time dt) {
  /// TODO another way
  auto strength = pheromone_strength_;
  pheromone_strength_ *= 1 - dt / active_time_;
  return strength;
}

