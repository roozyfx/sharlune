#include <iostream>

#include "render.h"
#include "render_nodes.h"
#include "types.h"

void render(UPtr<Camera> camera, UPtr<Film> film,
            const Ptr<RenderNodes>& world) {
  // Render loop
  for (size_t y = 0; y < camera->image_height(); ++y) {
    auto progress = float(y * 100) / static_cast<float>(camera->image_height());
    if ((y % 20) == 0) std::cout << "Progress: " << progress << "%\n";

    std::vector<int> row;
    row.reserve(camera->image_width() * film->num_channels());

    for (size_t x = 0; x < camera->image_width(); ++x) {
      Color pixel_color =
          film->max_val() * camera->sample_pixel_color(x, y, world);
      camera->write_pixel(std::move(pixel_color), row);
    }

    camera->write_line(row);
  }

  film->write(camera->data());
}
