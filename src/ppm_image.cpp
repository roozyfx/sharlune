#include "ppm_image.h"

#include <iostream>

#include "common.h"

PPMImage::PPMImage(std::string_view filename, const size_t width,
                   const size_t height, const int max_val,
                   const size_t num_channels)
    : filename_(std::move(filename)),
      width_(width),
      height_(height),
      max_val_(max_val),
      num_channels_(num_channels) {
  // Write the header
  file_ = std::ofstream(filename_, std::ios::out | std::ios::trunc);

  file_ << "P3\n" << width_ << ' ' << height_ << '\n' << max_val_ << '\n';
}

void PPMImage::write(const DataStorage& data) {
  if (!file_.is_open()) {
    std::clog << "Could not open file for writing\n";
    return;
  }

  std::clog << "Saving data to " << filename_ << std::endl;
  const auto fmax_val{static_cast<Float>(max_val_)};
  // TODO re-write more efficiently
  for (auto& row : data) {
    for (size_t i = 0; i < row.size(); ++i) {
      file_ << static_cast<int>(row[i] * fmax_val)
            << (i % num_channels_ == num_channels_ - 1 ? '\n' : ' ');
    }
  }
}
