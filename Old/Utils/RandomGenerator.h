//
// Created by Artem Novikov on 03.09.2022.
//

#ifndef ANTS__RANDOMGENERATOR_H_
#define ANTS__RANDOMGENERATOR_H_

#include <random>

#include "Vector.h"

class RandomGenerator {
 public:
  RandomGenerator(float min = -1.f, float max = 1.f);

  float GetValue();

  Vector2f GetVector2f();

 private:
  struct RandomHolder {
    RandomHolder(float min = -1.f, float max = 1.f) : device(), engine(device()), distribution(min, max) {}
    std::random_device device;
    std::default_random_engine engine;
    std::uniform_real_distribution<float> distribution;
  };

  static std::unique_ptr<RandomHolder> generator;
};

#endif //ANTS__RANDOMGENERATOR_H_
