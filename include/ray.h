#pragma once

#include "common.h"
#include "vectormath.h"

class Ray {
  Point3 origin_;
  Vec3 dir_;

 public:
  explicit Ray(const Point3& origin, const Vec3& direction)
      : origin_{origin}, dir_{direction} {}
  ~Ray() = default;

  inline Point3 at(const Float time) { return origin_ + time * dir_; }
  inline const Vec3& direction() const { return dir_; }
  inline const Point3& origin() const { return origin_; }
};

#endif