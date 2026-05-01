
#include <algorithm>
#include <cmath>

#include "basic_geometries.h"
#include "common.h"
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

bool hit_cube(const Cube &c, const Ray &r, const Interval &tt,
              HitRecord &record) {
  const double half_side{c.side() / 2.0};
  const Point3 center{c.center()};

  // Extract components into arrays for clean looping
  double ro[3] = {r.origin().x, r.origin().y, r.origin().z};
  double rd[3] = {r.direction().x, r.direction().y, r.direction().z};
  double min_pt[3] = {center.x - half_side, center.y - half_side,
                      center.z - half_side};
  double max_pt[3] = {center.x + half_side, center.y + half_side,
                      center.z + half_side};

  double t_min{-INF};
  double t_max{INF};

  // Slab Method for Ray-AABB Intersection
  for (int i = 0; i < 3; i++) {
    if (std::abs(rd[i]) < 1e-8) {
      // Ray is parallel to this axis. If origin is outside the slab, it's a
      // miss.
      if (ro[i] < min_pt[i] || ro[i] > max_pt[i]) {
        return false;
      }
    } else {
      double invD = 1.0 / rd[i];
      double t0 = (min_pt[i] - ro[i]) * invD;
      double t1 = (max_pt[i] - ro[i]) * invD;

      if (invD < 0.0) {
        std::swap(t0, t1);
      }

      t_min = std::max(t_min, t0);
      t_max = std::min(t_max, t1);

      // If the ray misses the box
      if (t_max <= t_min) {
        return false;
      }
    }
  }

  // Check Interval
  double t = t_min;
  if (!tt.surrounds(t)) {
    t = t_max;
    if (!tt.surrounds(t)) {
      return false;
    }
  }

  // Save to HitRecord
  record.t = t;

  // hit point = origin + t * direction
  record.p = Point3(r.origin().x + t * r.direction().x,
                    r.origin().y + t * r.direction().y,
                    r.origin().z + t * r.direction().z);

  // Calculate the normal
  Vec3 local_p(record.p.x - center.x, record.p.y - center.y,
               record.p.z - center.z);

  const double dx{std::abs(local_p.x)};
  const double dy{std::abs(local_p.y)};
  const double dz{std::abs(local_p.z)};

  if (dx >= dy && dx >= dz) {
    record.n = Vec3(local_p.x > 0 ? 1 : -1, 0, 0);
  } else if (dy >= dx && dy >= dz) {
    record.n = Vec3(0, local_p.y > 0 ? 1 : -1, 0);
  } else {
    record.n = Vec3(0, 0, local_p.z > 0 ? 1 : -1);
  }

  return true;
}
