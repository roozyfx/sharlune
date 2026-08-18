#include "render.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <thread>

#include "common.h"
#include "render_nodes.h"
#include "types.h"

void render_single_thread(Camera& camera, Film& film,
                          const RenderNodes* const world) {
  // Render loop
  for (size_t y = 0; y < camera.image_height(); ++y) {
    auto progress = float(y * 100) / static_cast<float>(camera.image_height());
    if ((y % 20) == 0) std::cout << "Progress: " << progress << "%\n";

    DataRow row;
    row.reserve(camera.image_width() * film.num_channels());

    for (size_t x = 0; x < camera.image_width(); ++x) {
      Color pixel_color =
          film.max_val() * camera.sample_pixel_color(x, y, world);
      camera.write_pixel(std::move(pixel_color), row);
    }

    camera.write_line(std::move(row));
  }

  film.write(camera.data());
}

void render(Camera& camera, Film& film, const RenderNodes* const world) {
  const auto img_height{camera.image_height()};
  const auto img_width{camera.image_width()};
  DataStorage rows(img_height);
  for (auto& row : rows) {
    row.reserve(img_width * film.num_channels());
  }

  const auto hardware_threads{std::thread::hardware_concurrency()};
  auto num_threads{
      std::max<size_t>(1, hardware_threads == 0 ? 1 : hardware_threads)};
  num_threads = 1;
  std::vector<std::thread> threads;
  threads.reserve(num_threads);
  const auto block_height{img_height / num_threads};

  auto block_render = [&](const size_t start_y, const size_t end_y) {
    for (size_t y = start_y; y < end_y; ++y) {
      DataRow& row = rows[y];
      row.reserve(img_width);
      for (size_t x = 0; x < img_width; ++x) {
        Color pixel_color{film.max_val() *
                          camera.sample_pixel_color(x, y, world)};
        camera.write_pixel(std::move(pixel_color), row);
      }
    }
  };

  for (size_t worker_number = 0; worker_number < num_threads; ++worker_number) {
    const auto start_y{worker_number * block_height};
    if (start_y >= img_height) break;
    const auto end_y{std::min(start_y + block_height, img_height)};
    threads.emplace_back(std::thread{block_render, start_y, end_y});
  }

  for (auto& thread : threads) {
    if (thread.joinable()) thread.join();
  }

  film.write(rows);
}
