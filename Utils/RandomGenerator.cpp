//
// Created by Artem Novikov on 03.09.2022.
//

#include "RandomGenerator.h"

std::unique_ptr<RandomGenerator::RandomHolder> RandomGenerator::generator = nullptr;

float RandomGenerator::GetValue() { return generator->distribution(generator->engine); }

Vector2f RandomGenerator::GetVector2f() {
  return {GetValue(), GetValue()};
}

RandomGenerator::RandomGenerator(float min, float max) {
  if (generator == nullptr) {
    generator = std::make_unique<RandomHolder>(min, max);
  }
}
