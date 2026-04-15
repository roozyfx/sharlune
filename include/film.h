#ifndef INCLUDE_FILEM_H_
#define INCLUDE_FILEM_H_
#include <cstddef>

#include "common.h"

class Film {
 public:
  virtual ~Film() = default;

  virtual constexpr size_t num_channels() const = 0;
  virtual constexpr int max_val() const = 0;
  virtual void write(const DataStorage&) = 0;
};

#endif  // INCLUDE_FILEM_H_