#ifndef INCLDUE_CAMERA_H_
#define INCLDUE_CAMERA_H_
#include <vector>

#include "common.h"
#include "vectormath.h"

/* Camera Interface */
class Camera {
 public:
  virtual ~Camera() = default;

  virtual constexpr Point3 center() const = 0;
  virtual constexpr size_t image_width() const = 0;
  virtual constexpr size_t image_height() const = 0;
  virtual DataStorage &data() = 0;
  virtual Point3 pixel_location(const size_t x, const size_t y) const = 0;
  virtual Vec3 ray_direction(const Point3 &pixel_center) const = 0;
  virtual void write_pixel(Color color, std::vector<int> &row) = 0;
  virtual void write_line(const std::vector<int> &row) = 0;
};

#endif  // INCLDUE_CAMERA_H_
