#ifndef INCLUDE_BASIC_GEOMETRIES_H_
#define INCLUDE_BASIC_GEOMETRIES_H_

#include "common.h"
#include "vectormath.h"

struct Sphere {
  Point3 center;
  Float radius;
  explicit Sphere(Point3 center, Float radius)
      : center{center}, radius{std::max<Float>(radius, Float(0))} {}
};

#endif  // INCLUDE_BASIC_GEOMETRIES_H_