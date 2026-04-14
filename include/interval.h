#ifndef INCLUDE_INTERVAL_H_
#define INCLUDE_INTERVAL_H_

#include <algorithm>

#include "common.h"

struct Interval {
  Float t_min;
  Float t_max;

  explicit Interval(Float tmin, const Float &tmax) : t_min{tmin}, t_max{tmax} {
    if (t_min >= t_max) std::swap(t_min, t_max);
  }
};

#endif  // INCLUDE_INTERVAL_H_