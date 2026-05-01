#include <exception>
#include <print>
#include <variant>

#include "pinhole_camera.h"
#include "rng.h"
#include "scatter.h"
#include "vectormath.h"

Point3 PinholeCamera::pixel_sample(const size_t x, const size_t y) const {
  const auto center{pixel_center_loc(x, y)};
  const auto half_u{u_length_ * 0.5};
  const auto half_v{v_length_ * 0.5};
  return Point3(center.x + random_number(-half_u, half_u),
                center.y + random_number(-half_v, half_v), -focal_length_);
}

Color PinholeCamera::ray_color(const Ray& r, const Ptr<RenderNodes>& world,
                               size_t depth) const {
  if (depth == 0) return Color();
  HitRecord rec;
  // Set the min interval to slightly larger than 0, to prevent 'trapped'
  // bounces due to floating-point rounding error.
  if (world and
      world->hit_all(r, Interval(0.001, std::numeric_limits<Float>::max()),
                     rec)) {
    Ray scattered_ray;
    Color attenuation;

    auto is_scattered = std::visit(
        [&](const auto& mat) {
          return Scatter{}(mat, r, rec, attenuation, scattered_ray);
        },
        rec.material);
    if (is_scattered) {
      return hadamard_product(ray_color(scattered_ray, world, depth - 1),
                              attenuation);
    }
    return Color(0, 255, 0);
  }

  Vec3 unit_direction;
  try {
    unit_direction = normalize(r.direction());
  } catch (std::exception& e) {
    std::println("{}", e.what());
  }
  auto a = 0.5 * (unit_direction.y + 1.0);
  return ((1.0 - a) * Color(0., 0., 1.) + a * Color(1., 1.0, 1.0));
}

Color PinholeCamera::sample_pixel_color(const size_t x, const size_t y,
                                        const Ptr<RenderNodes>& world) const {
  Color pixel_color;
  for (size_t sample_num = 0; sample_num < sample_per_pixel_; ++sample_num) {
    // TODO Bring the following 3 variables out of the loop
    Point3 sample = pixel_sample(x, y);
    Vec3 dir = ray_direction(sample);
    Ray r(cam_center_, dir);
    pixel_color += ray_color(r, world, max_depth_);
    // pixel_color += color_function(r, world, max_depth_);
    // Do Gamma correction on the pixel color
    // TODO Resolve problem (scale)
    /*
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));
*/
    // linear_to_gamma(std::move(pixel_color));
  }

  return pixel_color / static_cast<Float>(sample_per_pixel_);
}
