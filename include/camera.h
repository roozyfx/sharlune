#ifndef INCLDUE_CAMERA_H_
#define INCLDUE_CAMERA_H_
#include <cmath>
#include <vector>

#include "common.h"
#include "render_nodes.h"
#include "types.h"
#include "vectormath.h"

/* Camera Interface */
class Camera {
 public:
  virtual ~Camera() = default;

  virtual constexpr Point3 center() const = 0;
  virtual constexpr size_t image_width() const = 0;
  virtual constexpr size_t image_height() const = 0;
  virtual DataStorage &data() = 0;
  virtual void write_pixel(Color &&color, std::vector<int> &row) = 0;
  virtual void write_line(const std::vector<int> &row) = 0;
  virtual Color sample_pixel_color(const size_t x, const size_t y,
                                   const Ptr<RenderNodes> &world) const = 0;

 protected:
  inline void linear_to_gamma(Color &&color) const {
    color.x = std::sqrt(color.x);
    color.y = std::sqrt(color.y);
    color.z = std::sqrt(color.z);
  }
};

#endif  // INCLDUE_CAMERA_H_
