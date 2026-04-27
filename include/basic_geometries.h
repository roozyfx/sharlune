#ifndef INCLUDE_BASIC_GEOMETRIES_H_
#define INCLUDE_BASIC_GEOMETRIES_H_

#include "common.h"
#include "vectormath.h"

class Sphere {
  Point3 center_;
  Float radius_;

 public:
  explicit Sphere(Point3 center, Float radius)
      : center_{center}, radius_{std::max<Float>(radius, Float(0))} {}

  constexpr Point3 center() const { return center_; }
  constexpr Float radius() const { return radius_; }
};

class Cube {
  Point3 center_;
  Float side_;

 public:
  explicit Cube(const Point3 center, const Float side)
      : center_{center}, side_{std::max<Float>(side, Float(0))} {}

  constexpr Point3 center() const { return center_; }
  constexpr Float side() const { return side_; }
};

class Cylinder {
  Point3 center_;
  Float height_;
  Float radius_;

 public:
  explicit Cylinder(const Point3 c, const Float h, const Float r)
      : center_{c},
        height_{std::max<Float>(h, Float(0))},
        radius_{std::max<Float>(r, Float(0))} {}
  constexpr Point3 center() const { return center_; }
  constexpr Float height() const { return height_; }
  constexpr Float radius() const { return radius_; }
};
#endif  // INCLUDE_BASIC_GEOMETRIES_H_
