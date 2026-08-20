#include "pinhole_camera.h"

#include <exception>
#include <print>
#include <variant>

#include "rng.h"
#include "scatter.h"
#include "vectormath.h"

Point3 PinholeCamera::pixel_sample(const size_t x, const size_t y) const {
  const auto half_u{u_length_ * Float(0.5)};
  const auto half_v{v_length_ * Float(0.5)};
  return pixel_center_loc(x, y) + random_number(-half_u, half_u) * d_u_ +
         random_number(-half_v, half_v) * d_v_;
}

Color PinholeCamera::ray_color(const Ray& r, const RenderNodes* const world,
                               size_t depth) const {
  if (depth == 0) return Color();
  HitRecord rec;
  // Set the min interval to slightly larger than 0, to prevent 'trapped'
  // bounces due to floating-point rounding error.
  if (world and
      world->hit_all(
          r, Interval(Float(0.001), std::numeric_limits<Float>::max()), rec)) {
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
    return Color();
  }

  Vec3 unit_direction;
  try {
    unit_direction = normalize(r.direction());
  } catch (std::exception& e) {
    std::println("{}", e.what());
  }
  auto a = Float(0.5) * (unit_direction.y + Float(1));
  return ((Float(1) - a) * Color(Float(0), Float(0), Float(1)) +
          a * Color(Float(1), Float(1), Float(1)));
}

Color PinholeCamera::sample_pixel_color(const size_t x, const size_t y,
                                        const RenderNodes* const world) const {
  Color pixel_color;
  Point3 sample;
  Vec3 dir;
  Ray r;
  for (size_t sample_num = 0; sample_num < sample_per_pixel_; ++sample_num) {
    sample = pixel_sample(x, y);
    dir = ray_direction(sample);
    r.origin(cam_center_);
    r.direction(dir);
    pixel_color += ray_color(r, world, max_depth_);
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
