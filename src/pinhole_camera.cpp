#include "pinhole_camera.h"
#include "rng.h"
Point3 PinholeCamera::pixel_sample(const size_t x, const size_t y) const {
  const auto center{pixel_center_loc(x, y)};
  const auto half_u{u_length_ * 0.5};
  const auto half_v{v_length_ * 0.5};
  return Point3(center.x + random_number(-half_u, half_u),
                center.y + random_number(-half_v, half_v), -focal_length_);
}

Color PinholeCamera::sample_pixel_color(const size_t x, const size_t y,
                                        const std::shared_ptr<Hittables> &world,
                                        ColorFunction color_function) const {
  Color pixel_color(0, 0, 0);
  for (size_t sample_num = 0; sample_num < sample_per_pixel_; ++sample_num) {
    Point3 sample = pixel_sample(x, y);
    Vec3 dir = ray_direction(sample);
    Ray r(cam_center_, dir);
    pixel_color += color_function(r, world, max_depth_);
  }

  return pixel_color / sample_per_pixel_;
}