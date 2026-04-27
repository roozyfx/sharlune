#ifndef INCLUDE_HIT_RECORD_H_
#define INCLUDE_HIT_RECORD_H_
#include "common.h"
#include "ray.h"
#include "vectormath.h"

struct HitRecord {
  Point3 p{Point3{INF, INF, INF}};
  Vec3 n{Vec3(INF, INF, INF)};
  Float t{INF};
  bool front_face;

  HitRecord() = default;
  explicit HitRecord(Point3 hit_point, Vec3 normal, Float time)
      : p(hit_point), n(normal), t(time) {}
  void setFaceNormal(const Ray &r, Vec3 outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    n = front_face ? outward_normal : -outward_normal;
  }
};

#endif  // INCLUDE_HIT_RECORDE_H_
