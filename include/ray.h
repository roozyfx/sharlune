#ifndef INCLUDE_RAY_H_
#define INCLUDE_RAY_H_

#include "common.h"
#include "vectormath.h"

class Ray {
  Point3 origin_;
  Vec3 dir_;

 public:
  Ray() : origin_{Point3{}}, dir_{Vec3{}} {}
  explicit Ray(const Point3& origin, const Vec3& direction)
      : origin_{origin}, dir_{direction} {}
  Ray(const Ray&) = default;
  Ray& operator=(const Ray&) = default;
  ~Ray() = default;

  inline Point3 at(const Float time) const { return origin_ + time * dir_; }
  inline const Vec3& direction() const { return dir_; }
  inline const Point3& origin() const { return origin_; }
};

#endif
