#include <filesystem>
#include <iostream>

#include "ppm.h"

namespace fs = std::filesystem;

PPMImage::PPMImage(std::string_view filename, const size_t width,
                   const size_t height, const int max_val)
    : filename_(std::move(filename)),
      width_(width),
      height_(height),
      max_val_(max_val) {
  // TODO Probably not the best solution to fully overwrite the file
  if (fs::exists(filename_)) {
    fs::remove(filename_);
  }
  file_ = std::ofstream(filename_, std::ios::out | std::ios::app);
  file_ << "P3\n" << width_ << ' ' << height_ << '\n' << max_val_ << '\n';
  file_.close();
}

void PPMImage::write(const std::vector<std::vector<int>> &data) {
  file_.open(filename_, std::ios::out | std::ios::app | std::ios::ate);
  if (!file_.is_open()) {
    std::clog << "could not open file for writing\n";
    return;
  }

  for (const auto &row : data) {
    for (const auto &el : row) {
      file_ << el << ' ';
    }
    file_ << '\n';
  }
}
