#ifndef INCLUDE_EXR_IMAGE_H_
#define INCLUDE_EXR_IMAGE_H_

#include <cstddef>
#include <fstream>
#include <string_view>

#include "common.h"
#include "configuration.h"
#include "film.h"

/* An extremely simple EXR Image class*/

class EXRImage : public Film {
  std::string filename_;
  size_t width_;
  size_t height_;
  int max_val_;
  std::ofstream file_;
  // TODO
  size_t num_channels_{3};

 public:
  explicit EXRImage(std::string_view filename, const size_t width,
                    const size_t height, const int max_val,
                    const size_t num_channels = 3);

  explicit EXRImage(const ImageConfig& config, const size_t width,
                    const size_t height)
      : EXRImage(config.filename, width, height, config.max_val,
                 config.num_channels) {}

  ~EXRImage() override = default;

  EXRImage(const EXRImage&) = delete;
  EXRImage(EXRImage&&) = default;
  void write(const DataStorage& data) override;

  constexpr inline size_t width() const { return width_; }
  constexpr inline size_t height() const { return height_; }
  constexpr inline int max_val() const final { return max_val_; }
  constexpr inline size_t num_channels() const final { return num_channels_; }
};

#endif  // INCLUDE_EXR_IMAGE_H_
