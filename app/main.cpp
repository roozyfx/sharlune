#include <cstdlib>
#include <memory>
#include <utility>

#include "film.h"
#include "pinhole_camera.h"
#include "ppm.h"
#include "render.h"
#include "scene.h"
#include "types.h"
#include "vectormath.h"

int main() {
  // Create the scene to render
  auto world{create_world()};

  // Create a camera
  std::unique_ptr<Camera> camera =
      std::make_unique<PinholeCamera>(Point3(), 640, 16. / 9.);

  // Set film (image) parameters
  const size_t num_channels{3};
  const size_t max_val{65535};
  UPtr<Film> image =
      std::make_unique<PPMImage>("spheres.ppm", camera->image_width(),
                                 camera->image_height(), max_val, num_channels);
  // Render loop
  if (camera && image && world)
    render(std::move(camera), std::move(image), std::move(world));

  return EXIT_SUCCESS;
}
