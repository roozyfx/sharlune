#ifndef INCLUDE_MATERIAL_H_
#define INCLUDE_MATERIAL_H_
#include <variant>

#include "vectormath.h"

// TODO
struct Metal {
  Color albedo;
  Float fuzz;
};
struct Lambertian {
  Color albedo;
};

struct Dielectric {
  Color albedo;
  Float refraction_index;

  static double reflectance(double cosine, double refraction_index);
};

using Material = std::variant<Metal, Lambertian, Dielectric>;

#endif  // INCLUDE_COLOR_FUNCTIONS_H_
