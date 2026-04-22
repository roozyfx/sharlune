#include <random>

#include "rng.h"
#include "vectormath.h"

/*
Generate random number in range [0, 1]
*/
Float random_number() {
  static std::uniform_real_distribution<Float> distribution(Float(0),
                                                            Float(1.));
  static std::random_device rd;
  static std::mt19937 generator(rd());

  return distribution(generator);
}

/*
Generate random number in range [min, max]
*/
Float random_number(const Float min, const Float max) {
  return min + (max - min) * random_number();
}