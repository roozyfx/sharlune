#include <iostream>
#include <memory>

#include "render.h"
void render(std::unique_ptr<Camera> camera, std::unique_ptr<Film> film,
            const std::shared_ptr<Hittables>& world,
            ColorFunction color_function) {
  // Render loop
  for (size_t y = 0; y < camera->image_height(); ++y) {
    auto progress = float(y * 100) / camera->image_height();
    std::cout << "Progress: " << progress << "%\n";
    std::vector<int> row;
    row.reserve(camera->image_width() * film->num_channels());
    for (size_t x = 0; x < camera->image_width(); ++x) {
      Point3 pixel_center = camera->pixel_location(x, y);
      Vec3 dir = camera->ray_direction(pixel_center);
      Ray r(camera->center(), dir);

      Color pixel_color = film->max_val() * color_function(r, world);
      camera->write_pixel(pixel_color, row);
    }

    camera->write_line(row);
  }

  film->write(camera->data());
}