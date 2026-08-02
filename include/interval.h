#ifndef INCLUDE_INTERVAL_H_
#define INCLUDE_INTERVAL_H_

#include "common.h"

struct Interval {
  Float min{INF};
  Float max{-INF};

  Interval() = default;
  explicit Interval(Float minimum, const Float& maximum)
      : min{minimum}, max{maximum} {}

  inline constexpr Float size() const { return max - min; }

  inline bool contains(const Float val) const {
    return val >= min and val <= max;
  }

  inline bool surrounds(const Float val) const {
    return val > min and val < max;
  }

  static const Interval& empty();
  static const Interval& universe();
};

#endif  // INCLUDE_INTERVAL_H_
