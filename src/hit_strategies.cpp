#include <cmath>

#include "basic_geometries.h"
#include "hit_record.h"
#include "hit_strategies.h"
#include "interval.h"
#include "ray.h"
#include "vectormath.h"

bool hit_sphere(const Sphere &s, const Ray &r, const Interval &tt,
                HitRecord &record) {
  const auto d = r.direction();
  const auto oc = s.center() - r.origin();

  const auto a = length_squared(d);
  const auto h = dot(d, oc);
  const auto c = length_squared(oc) - s.radius() * s.radius();

  const auto discriminant = h * h - a * c;
  if (discriminant < 0) return false;
  const auto sqrtdisc = std::sqrt(discriminant);

  auto root = (h - sqrtdisc) / a;
  if (!tt.surrounds(root)) {
    root = (h + sqrtdisc) / a;
    if (!tt.surrounds(root)) {
      return false;
    }
  }

  // save hit information to record
  record.p = r.at(root);
  record.t = root;
  auto outward_normal = (record.p - s.center()) / s.radius();
  record.setFaceNormal(r, outward_normal);

  return true;
}
