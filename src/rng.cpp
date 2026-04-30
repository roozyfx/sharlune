#include <random>

#include "rng.h"
#include "vectormath.h"

/*
Generate random number in range [0, 1]
*/
Float random_number() {
  static std::uniform_real_distribution<Float> distribution(Float(0),
                                                            Float(1.));
  static std::mt19937 generator(std::random_device{}());

  return distribution(generator);
}

/*
Generate random number in range [min, max]
*/
Float random_number(const Float min, const Float max) {
  return min + (max - min) * random_number();
}

/*
Generate random Vec3 with each element in range [min, max]
*/
Vec3 random_vec3(const Float min, const Float max) {
  return Vec3(random_number(min, max), random_number(min, max),
              random_number(min, max));
}

// Generate a uniformly distributed unit vector on the unit-sphere
Vec3 random_unit_vector() {
  while (true) {
    // generate a random vector in [-1, -1] cube
    Vec3 v = random_vec3(-1, 1);
    if (length_squared(v) >= 1e-160 and length_squared(v) <= 1) {
      return normalize(v);
    }
  }
}

Vec3 random_on_half_sphere(const Vec3 &normal) {
  auto u{random_unit_vector()};
  return dot(u, normal) > Float(0.) ? u : -u;
}
