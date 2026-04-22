#ifndef INCLDUE_CAMERA_H_
#define INCLDUE_CAMERA_H_
#include <functional>
#include <memory>
#include <vector>

#include "common.h"
#include "hittables.h"
#include "vectormath.h"

using ColorFunction = std::function<Color(
    const Ray &r, std::shared_ptr<Hittables> world, size_t depth)>;

/* Camera Interface */
class Camera {
 public:
  virtual ~Camera() = default;

  virtual constexpr Point3 center() const = 0;
  virtual constexpr size_t image_width() const = 0;
  virtual constexpr size_t image_height() const = 0;
  virtual DataStorage &data() = 0;
  virtual void write_pixel(Color color, std::vector<int> &row) = 0;
  virtual void write_line(const std::vector<int> &row) = 0;
  virtual Color sample_pixel_color(const size_t x, const size_t y,
                                   const std::shared_ptr<Hittables> &world,
                                   ColorFunction color_function) const = 0;
};

#endif  // INCLDUE_CAMERA_H_
