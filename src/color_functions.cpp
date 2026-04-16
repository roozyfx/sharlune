#include "color_functions.h"

Color sample_colorize(const Ray& r, const std::shared_ptr<Hittables>& world) {
  HitRecord rec;
  if (world->hit_all(r, Interval(0, 100), rec)) {
    const auto n{rec.n};
    return Color(n.x + 1, n.y + 1, n.z + 1) * 0.5;
  }

  Vec3 unit_direction = normalize(r.direction());
  auto a = 0.5 * (unit_direction.y + 1.0);
  return ((1.0 - a) * Color(0., 0., 1.) + a * Color(1., 1.0, 1.0));
}