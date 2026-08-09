#include "exr_image.h"

#include <ImfArray.h>
#include <ImfRgbaFile.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "common.h"

using namespace OPENEXR_IMF_NAMESPACE;

EXRImage::EXRImage(std::string_view filename, const size_t width,
                   const size_t height, const int max_val,
                   const size_t num_channels)
    : filename_(std::move(filename)),
      width_(width),
      height_(height),
      max_val_(max_val),
      num_channels_(num_channels) {}

void EXRImage::write(const DataStorage& data) {
  // Flatten data:
  std::vector<half> flat_data;
  flat_data.reserve(height_ * width_ * num_channels_);
  for (auto& row : data) {
    std::copy(row.cbegin(), row.cend(), std::back_inserter(flat_data));
  }

  Array2D<Rgba> pixels(static_cast<long>(height_), static_cast<long>(width_));
  for (int y = 0; y < static_cast<int>(height_); y++) {
    for (int x = 0; x < static_cast<int>(width_); x++) {
      auto xx{static_cast<size_t>(x)};
      auto yy{static_cast<size_t>(y)};
      pixels[y][x] = Rgba(flat_data[yy * 3 * width_ + xx * 3 + 0],
                          flat_data[yy * 3 * width_ + xx * 3 + 1],
                          flat_data[yy * 3 * width_ + xx * 3 + 2], Float(1));
    }
  }

  try {
    RgbaOutputFile file(filename_.c_str(), static_cast<int>(width_),
                        static_cast<int>(height_), WRITE_RGBA);
    file.setFrameBuffer(&pixels[0][0], 1, width_);
    file.writePixels(static_cast<int>(height_));
  } catch (const std::exception& e) {
    std::cerr << "error writing image file stripes.exr:" << e.what()
              << std::endl;
  }
}
