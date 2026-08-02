#ifndef INCLUDE_RNG_H_
#define INCLUDE_RNG_H_

#include "common.h"
#include "vectormath.h"

Float random_number();
Float random_number(const Float min, const Float max);

Vec3 random_vec3(const Float min, const Float max);

Vec3 random_unit_vector();
Vec3 random_on_half_sphere(const Vec3& normal);

#endif  // INCLUDE_RNG_H_
