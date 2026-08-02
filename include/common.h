#ifndef INCLUDE_COMMON_GEOMETRIES_H_
#define INCLUDE_COMMON_GEOMETRIES_H_
#include <limits>
#include <numbers>
#include <vector>

using Float = double;
using DataRow = std::vector<int>;
using DataStorage = std::vector<DataRow>;

constexpr const Float INF = std::numeric_limits<Float>::infinity();
constexpr const Float PI = static_cast<Float>(std::numbers::pi);
constexpr const Float VERY_SMALL = 1E-8;

constexpr Float degrees_to_radians(const Float degrees) {
  return static_cast<Float>(degrees * PI / 180.0);
}

#endif  // INCLUDE_COMMON_GEOMETRIES_H_
