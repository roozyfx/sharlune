#ifndef INCLUDE_CONFIGURATION_H_
#define INCLUDE_CONFIGURATION_H_
// Don't want exceptions with Toml++
#define TOML_EXCEPTIONS 0
#include <toml++/toml.hpp>

#include "vectormath.h"

// Camera specific settings
struct CameraConfig {
  Point3 center;
  size_t image_width;
  size_t image_height;
  double aspect_ratio;
  size_t sample_per_pixel;
  size_t max_depth;
  double focal_length;
  double vertical_fov;
};

// Image settings
struct ImageConfig {
  std::string filename;
  int max_val;
  size_t num_channels;
};

// Aggregate Configuration
struct Configuration {
  CameraConfig camera;
  ImageConfig image;
};

Configuration loadConfig(const std::string &);

#endif  // INCLUDE_CONFIGURATION_H_
