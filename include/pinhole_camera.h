#ifndef INCLUDE_PINHOLE_CAMERA_H_
#define INCLUDE_PINHOLE_CAMERA_H_
#include <cstddef>

#include "camera.h"
#include "common.h"
#include "vectormath.h"
class PinholeCamera : public Camera {
 public:
  explicit PinholeCamera(const Point3 &center, const size_t image_width = 800,
                         const Float aspect_ratio = 16. / 9.,
                         const Float focal_length = 1.,
                         const Float viewport_height = 2.,
                         const size_t sample_per_pixel = 100)
      : cam_center_(center),
        image_width_(image_width),
        aspect_ratio_(aspect_ratio),
        sample_per_pixel_(sample_per_pixel),
        focal_length_(focal_length),
        viewport_height_(viewport_height) {
    data_.reserve(image_height_);
  }

  ~PinholeCamera() = default;

  inline constexpr Point3 center() const override { return cam_center_; }
  inline constexpr size_t image_width() const override { return image_width_; }
  inline constexpr size_t image_height() const override {
    return image_height_;
  }

  inline DataStorage &data() override { return data_; }

  // TODO Improve efficiency
  inline void write_pixel(Color color, std::vector<int> &row) override {
    row.push_back(color.x);
    row.push_back(color.y);
    row.push_back(color.z);
  }

  // TODO Improve efficiency
  inline void write_line(const DataStorage &row) override {
    for (const auto &el : row) data_.push_back(el);
  }

  Color sample_pixel_color(const size_t x, const size_t y,
                           const std::shared_ptr<Hittables> &world,
                           ColorFunction color_function) const override;

 private:
  constexpr const Point3 pixel00_center_loc() const {
    const Point3 viewport_top_left = cam_center_ + Vec3(0, 0, -focal_length_) -
                                     viewport_u_ * 0.5 - viewport_v_ * 0.5;
    return viewport_top_left + d_u_ * 0.5 + d_v_ * 0.5;
  }

  inline Point3 pixel_center_loc(const size_t x, const size_t y) const {
    return pixel00_center_loc() + x * d_u_ + y * d_v_;
  }

  Point3 pixel_sample(const size_t x, const size_t y) const;

  inline Vec3 ray_direction(const Point3 &pixel_center) const {
    return pixel_center - cam_center_;
  }

  Point3 cam_center_ = Point3(0., 0., 0.);
  size_t image_width_{800};
  Float aspect_ratio_{16. / 9.};
  size_t image_height_ =
      std::max(static_cast<Float>(image_width_) / aspect_ratio_, 1.);
  size_t sample_per_pixel_{100};

  Float focal_length_{1.};
  Float viewport_height_{2.0};
  Float viewport_width_ = viewport_height_ * static_cast<Float>(image_width_) /
                          static_cast<Float>(image_height_);
  Vec3 viewport_u_{Vec3(viewport_width_, 0, 0)};
  Vec3 viewport_v_{Vec3(0, -viewport_height_, 0)};

  Float u_length_{viewport_width_ / image_width_};
  Float v_length_{viewport_height_ / image_height_};
  Vec3 d_u_{Vec3(u_length_, 0, 0)};
  Vec3 d_v_{Vec3(0, -v_length_, 0)};

  DataStorage data_{};
};

#endif  // INCLUDE_PINHOLE_CAMERA_H_