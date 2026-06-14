#ifndef INCLUDE_PINHOLE_CAMERA_H_
#define INCLUDE_PINHOLE_CAMERA_H_
#include <cstddef>

#include "camera.h"
#include "common.h"
#include "configuration.h"
#include "vectormath.h"

class PinholeCamera : public Camera {
 public:
  explicit PinholeCamera(const Point3 &look_from, const Point3 &look_at,
                         const Vec3 &v_up, const size_t image_width = 800,
                         const Float aspect_ratio = 16. / 9.,
                         const Float vertical_fov = 90.,
                         const size_t sample_per_pixel = 100,
                         const size_t max_depth = 50)
      : cam_center_(look_from),
        cam_look_at_(look_at),
        cam_v_up_(v_up),
        image_width_(image_width),
        aspect_ratio_(aspect_ratio),
        vertical_fov_(vertical_fov),
        sample_per_pixel_(sample_per_pixel),
        max_depth_(max_depth) {
    image_height_ = static_cast<size_t>(
        std::max(static_cast<Float>(image_width_) / aspect_ratio_, 1.));
    focal_length_ = length(cam_center_ - cam_look_at_);
    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w_ = normalize(cam_center_ - cam_look_at_);
    u_ = normalize(cross(cam_v_up_, w_));
    v_ = cross(w_, u_);

    viewport_height_ = vfov2veiwport_height(vertical_fov_, focal_length_);
    viewport_width_ = viewport_height_ *
                      (double(image_width_) / static_cast<Float>(image_width_));

    viewport_u_ = viewport_width_ * u_;
    viewport_v_ = -viewport_height_ * v_;

    u_length_ = viewport_width_ / static_cast<Float>(image_width_);
    v_length_ = viewport_height_ / static_cast<Float>(image_height_);
    d_u_ = Vec3(u_length_, 0, 0);
    d_v_ = Vec3(0, -v_length_, 0);

    data_.reserve(image_height_);
  }

  explicit PinholeCamera(const CameraConfig &config)
      : PinholeCamera(config.look_from, config.look_at, config.v_up,
                      config.image_width, config.aspect_ratio,
                      config.vertical_fov, config.sample_per_pixel,
                      config.max_depth) {}

  ~PinholeCamera() override = default;

  inline constexpr Point3 center() const override { return cam_center_; }
  inline constexpr size_t image_width() const override { return image_width_; }
  inline constexpr size_t image_height() const override {
    return image_height_;
  }

 inline DataStorage &data() override { return data_; }

 // TODO Improve efficiency
 inline void write_pixel(Color &&color, std::vector<int> &row) override {
   row.push_back(static_cast<int>(color.x));
   row.push_back(static_cast<int>(color.y));
   row.push_back(static_cast<int>(color.z));
 }

  // TODO Improve efficiency
  inline void write_line(const DataStorage &row) override {
    for (const auto &el : row) data_.push_back(el);
  }

  Color sample_pixel_color(const size_t x, const size_t y,
                           const RenderNodes *const world) const override;

 private:
  constexpr const Point3 pixel00_center_loc() const {
    const Point3 viewport_top_left = cam_center_ - focal_length_ * w_ -
                                     viewport_u_ * 0.5 - viewport_v_ * 0.5;
    return viewport_top_left + d_u_ * 0.5 + d_v_ * 0.5;
  }

  inline Point3 pixel_center_loc(const size_t x, const size_t y) const {
    return pixel00_center_loc() + static_cast<Float>(x) * d_u_ + static_cast<Float>(y) * d_v_;
  }

  Point3 pixel_sample(const size_t x, const size_t y) const;

  inline Vec3 ray_direction(const Point3 &pixel_center) const {
    return pixel_center - cam_center_;
  }

  Color ray_color(const Ray &r, const RenderNodes *const world,
                  size_t depth) const;

  Float vfov2veiwport_height(const Float vfov, const Float focal_length) const {
    // Convert to Radians
    auto theta{0.0174533 * vfov};
    auto h{std::tan(theta / 2)};
    return 2 * h * focal_length;
  }

  Point3 cam_center_ = Point3(0., 0., 0.);
  Point3 cam_look_at_ = Point3(0., 0., -1.);
  Vec3 cam_v_up_ = Vec3(0., 1., 0.);

  size_t image_width_{800};
  Float aspect_ratio_{16. / 9.};
  size_t image_height_ = static_cast<size_t>(
      std::max(static_cast<Float>(image_width_) / aspect_ratio_, 1.));

  Float focal_length_{1.};
  Float vertical_fov_{90.};
  Float viewport_height_{vfov2veiwport_height(vertical_fov_, focal_length_)};
  Float viewport_width_ = viewport_height_ * static_cast<Float>(image_width_) /
                          static_cast<Float>(image_height_);
  Vec3 viewport_u_{Vec3(viewport_width_, 0, 0)};
  Vec3 viewport_v_{Vec3(0, -viewport_height_, 0)};

  Float u_length_{viewport_width_ / image_width_};
  Float v_length_{viewport_height_ / image_height_};
  Vec3 d_u_{Vec3(u_length_, 0, 0)};
  Vec3 d_v_{Vec3(0, -v_length_, 0)};
  Vec3 u_, v_, w_;

  size_t sample_per_pixel_{10};
  size_t max_depth_{7};
  DataStorage data_{};
};

#endif  // INCLUDE_PINHOLE_CAMERA_H_
