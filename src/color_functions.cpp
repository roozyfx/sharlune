#include <limits>

#include "color_functions.h"
#include "rng.h"

Color sample_colorize(const Ray& r, const std::shared_ptr<Hittables>& world,
                      size_t) {
  HitRecord rec;
  if (world->hit_all(r, Interval(0, 100), rec)) {
    const auto n{rec.n};
    return Color(n.x + 1, n.y + 1, n.z + 1) * 0.5;
  }

  Vec3 unit_direction = normalize(r.direction());
  auto a = 0.5 * (unit_direction.y + 1.0);
  return ((1.0 - a) * Color(0., 0., 1.) + a * Color(1., 1.0, 1.0));
}

Color naive_diffuse(const Ray& r, const std::shared_ptr<Hittables>& world,
                    size_t depth) {
  if (depth == 0) return Color(0, 0, 0);
  HitRecord rec;
  // Set the min interval to slightly larger than 0, to prevent 'trapped'
  // bounces due to floating-point rounding error.
  if (world->hit_all(r, Interval(0.001, std::numeric_limits<Float>::max()),
                     rec)) {
    Vec3 direction = random_on_half_sphere(rec.n);
    return naive_diffuse(Ray(rec.p, direction), world, depth - 1) * 0.5;
  }

  Vec3 unit_direction = normalize(r.direction());
  auto a = 0.5 * (unit_direction.y + 1.0);
  return ((1.0 - a) * Color(0., 0., 1.) + a * Color(1., 1.0, 1.0));
}