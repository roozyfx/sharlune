#include <cstdlib>
#include <memory>
#include <utility>

#include "film.h"
#include "pinhole_camera.h"
#include "ppm.h"
#include "render.h"
#include "scene.h"
#include "vectormath.h"

int main() {
  // Create the scene to render
  auto world{create_world()};

  // Create a camera
  std::unique_ptr<Camera> camera =
      std::make_unique<PinholeCamera>(Point3(0., 0., 0.));

  // Set film (image) parameters
  const size_t num_channels{3};
  const size_t max_val{65535};
  std::unique_ptr<Film> image =
      std::make_unique<PPMImage>("spheres.ppm", camera->image_width(),
                                 camera->image_height(), max_val, num_channels);

  // Render loop
  render(std::move(camera), std::move(image), world, naive_diffuse);
  return EXIT_SUCCESS;
}
