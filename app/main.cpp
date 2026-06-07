#include <cstdlib>
#include <memory>
#include <utility>

#include "configuration.h"
#include "film.h"
#include "pinhole_camera.h"
#include "ppm.h"
#include "render.h"
#include "scene.h"
#include "types.h"

int main(int argc, char **argv) {
  const auto config_file = (argc == 2) ? argv[1] : "configuration.toml";
  const auto config{loadConfig(config_file)};

  // Create the scene to render
  auto world{create_world()};

  // Create a camera
  std::unique_ptr<Camera> camera =
      std::make_unique<PinholeCamera>(config.camera);

  // Set film (image) parameters
  UPtr<Film> image = std::make_unique<PPMImage>(
      config.image, camera->image_width(), camera->image_height());

  // Render loop
  if (camera && image && world)
    render(std::move(camera), std::move(image), world.get());

  return EXIT_SUCCESS;
}
