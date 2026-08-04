#ifndef INCLUDE_COMMON_GEOMETRIES_H_
#define INCLUDE_COMMON_GEOMETRIES_H_
#include <limits>
#include <numbers>
#include <vector>

using Float = float;
using DataRow = std::vector<Float>;
using DataStorage = std::vector<DataRow>;

constexpr const Float INF = std::numeric_limits<Float>::infinity();
constexpr const Float PI = static_cast<Float>(std::numbers::pi);
constexpr const Float VERY_SMALL = Float(1E-8);

constexpr Float degrees_to_radians(const Float degrees) {
  return static_cast<Float>(degrees * PI / Float(180));
}

#endif  // INCLUDE_COMMON_GEOMETRIES_H_
