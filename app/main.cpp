#include <cstdlib>
#include <iostream>
#include <memory>
#include <print>
#include <utility>

#include "configuration.h"
#include "exr_image.h"
#include "film.h"
#include "pinhole_camera.h"
#include "ppm_image.h"
#include "render.h"
#include "scene.h"
#include "types.h"

int main(int argc, char** argv) {
  const auto config_file = (argc == 2) ? argv[1] : "configuration.toml";
  const auto config{loadConfig(config_file)};

  // Create the scene to render
  auto world{create_world()};

  // Create a camera
  std::unique_ptr<Camera> camera =
      std::make_unique<PinholeCamera>(config.camera);

  // Set film (image) parameters
  UPtr<Film> image;
  auto file_format{config.image.file_format};
  std::println("Rendering scene and saving to {}", config.image.filename);
  if (file_format.compare("exr") == 0) {
    image = std::make_unique<EXRImage>(config.image, camera->image_width(),
                                       camera->image_height());
  } else if (file_format.compare("ppm") == 0) {
    image = std::make_unique<PPMImage>(config.image, camera->image_width(),
                                       camera->image_height());
  } else {
    std::cerr << "Error: Invalid file format! Please choose a supported format "
                 "in the configuration file."
              << std::endl;
    return EXIT_FAILURE;
  }

  // Render loop
  if (camera && image && world) render(*camera, *image, world.get());

  return EXIT_SUCCESS;
}
