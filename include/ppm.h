#ifndef INCLUDE_PPM_H_
#define INCLUDE_PPM_H_

#include <cstddef>
#include <fstream>
#include <string_view>
#include <vector>

#include "common.h"

/* An extremely simple PPM Image class*/

class PPMImage {
  std::string filename_;
  size_t width_;
  size_t height_;
  Float max_val_;
  std::ofstream file_;

 public:
  explicit PPMImage(std::string_view filename, const size_t width,
                    const size_t height, const int max_val);

  ~PPMImage() {
    if (file_.is_open()) file_.close();
  }

  void write(const std::vector<std::vector<int>> &data);
};

#endif  // INCLUDE_PPM_H_