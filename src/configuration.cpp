// #include <toml++/impl/table.hpp>

#include <iostream>

#include "configuration.h"
#include "vectormath.h"

Configuration loadConfig(const std::string& filepath) {
  Configuration config;

  // Parse the TOML file into a table
  auto result = toml::parse_file(filepath);
  if (!result) {
    std::cerr << "Configuration file parsing failed:\n"
              << result.error() << std::endl;
    return {};
  }
  toml::table tbl = std::move(result.table());

  // Parse [Camera]
  // Safely extract the center array
  auto center_arr = tbl["Camera"]["center"].as_array();
  if (center_arr && center_arr->size() == 3) {
    config.camera.center =
        Point3{center_arr->at(0).value_or(0.0), center_arr->at(1).value_or(0.0),
               center_arr->at(2).value_or(0.0)};
  } else {
    config.camera.center = Point3{0.0, 0.0, 0.0};  // Default fallback
  }

  config.camera.image_width =
      tbl["Camera"]["image_width"].value_or(static_cast<size_t>(800));
  config.camera.image_height =
      tbl["Camera"]["image_height"].value_or(static_cast<size_t>(450));
  config.camera.aspect_ratio = tbl["Camera"]["aspect_ratio"].value_or(16. / 9.);
  config.camera.sample_per_pixel =
      tbl["Camera"]["sample_per_pixel"].value_or(static_cast<size_t>(10));
  config.camera.max_depth =
      tbl["Camera"]["max_depth"].value_or(static_cast<size_t>(7));
  config.camera.focal_length = tbl["Camera"]["focal_length"].value_or(1.0);
  config.camera.viewport_height =
      tbl["Camera"]["viewport_height"].value_or(2.0);

  // Parse [Image]
  config.image.filename = tbl["Image"]["filename"].value_or("output.ppm");
  config.image.max_val = tbl["Image"]["max_val"].value_or(65535);
  config.image.num_channels =
      tbl["Image"]["num_channels"].value_or(static_cast<size_t>(3));

  return config;
}
