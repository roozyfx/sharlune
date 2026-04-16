#include <random>

#include "rng.h"

Float random_number() {
  static std::uniform_real_distribution<Float> distribution;
  static std::mt19937 generator;

  return distribution(generator);
}

Float random_number(const Float min, const Float max) {
  return min + (max - min) * random_number();
}