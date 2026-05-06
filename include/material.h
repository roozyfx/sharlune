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

using Material = std::variant<Metal, Lambertian>;

#endif  // INCLUDE_COLOR_FUNCTIONS_H_
