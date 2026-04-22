#ifndef INCLUDE_INTERVAL_H_
#define INCLUDE_INTERVAL_H_

#include "common.h"

struct Interval {
  Float min{INF};
  Float max{-INF};

  Interval() = default;
  explicit Interval(Float min, const Float &max) : min{min}, max{max} {}

  inline constexpr Float size() const { return max - min; }

  inline bool contains(const Float val) const {
    return val >= min and val <= max;
  }

  inline bool surrounds(const Float val) const {
    return val > min and val < max;
  }

  static const Interval empty, universe;
};

#endif  // INCLUDE_INTERVAL_H_