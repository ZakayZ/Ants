//
// Created by Artem Novikov on 02.05.2023.
//

#ifndef ANTS_UTILS_RANDOMIZER_H_
#define ANTS_UTILS_RANDOMIZER_H_

#include <random>
#include <numbers>

#include "Vector.h"

namespace Random {
static inline std::random_device device;
static inline std::mt19937 generator(device());

template <typename RealType>
RealType UniformRealDistribution() {
  static std::uniform_real_distribution<RealType> distribution(0, 1);
  return distribution(generator);
}

template <typename RealType>
static double NormalDistribution(RealType mean = 0, RealType deviation = 1) {
  static std::normal_distribution<RealType> distribution(0, 1);
  return distribution(generator);
}

template <typename RealType, size_t Dim>
static Vector<RealType, Dim> UniformRealVector() {
  Vector<RealType, Dim> v;
  for (size_t i = 0; i < Dim; ++i) {
    v[i] = UniformRealDistribution<RealType>();
  }

  return v;
}

template <typename RealType, size_t Dim>
static Vector<RealType, Dim> IsotropicVector(RealType magnitude = 1) {
  Vector<RealType, Dim> v;
  for (size_t i = 0; i < Dim; ++i) {
    v[i] = NormalDistribution<RealType>();
  }

  return v * (magnitude / v.Length());
}

template <typename RealType>
static Vector<RealType, 2> IsotropicVector(RealType magnitude) {
  auto phi = 2 * std::numbers::pi * UniformRealDistribution<RealType>();

  return {std::cos(phi) * magnitude, std::sin(phi) * magnitude};
}

template <typename RealType>
static Vector<RealType, 2> IsotropicVector() {
  auto phi = 2 * std::numbers::pi * UniformRealDistribution<RealType>();

  return {std::cos(phi), std::sin(phi)};
}

template <typename RealType>
static Vector<RealType, 3> IsotropicVector(RealType magnitude) {
  auto cos = 1.0 - 2.0 * UniformRealDistribution<RealType>();
  auto sin = std::sqrt(1.0 - std::pow(cos, 2));
  auto phi = std::numbers::pi * UniformRealDistribution<RealType>();
  return {magnitude * std::cos(phi) * sin, magnitude * std::sin(phi) * sin, magnitude * cos};
}

template <typename RealType>
static Vector<RealType, 3> IsotropicVector() {
  auto cos = 1.0 - 2.0 * UniformRealDistribution<RealType>();
  auto sin = std::sqrt(1.0 - std::pow(cos, 2));
  auto phi = std::numbers::pi * UniformRealDistribution<RealType>();
  return {std::cos(phi) * sin, std::sin(phi) * sin, cos};
}
};

#endif //ANTS_UTILS_RANDOMIZER_H_
