//
// Created by Artem Novikov on 09.05.2023.
//

#include "PheromoneGland.h"

PheromoneGland::PheromoneGland() : pheromone_strength_(0), effective_time_(1), type_(None) {}

PheromoneGland::PheromoneGland(Float initial_strength, Time effective_time, PheromoneType type)
    : pheromone_strength_(initial_strength), effective_time_(effective_time), type_(type) {}

Float PheromoneGland::Secrete(Time dt) {
  /// TODO another way maybe
  auto strength = pheromone_strength_;
  pheromone_strength_ *= 1 - dt / effective_time_;
  return strength;
}

void PheromoneGland::SetPheromoneType(PheromoneType type) {
  type_ = type;
}

void PheromoneGland::Reset(Float strength) {
  pheromone_strength_ = strength;
}

