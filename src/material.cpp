#include "material.h"

Float Dielectric::reflectance(Float cosine, Float refraction_index) {
  // Use Schlick's approximation for reflectance.
  Float r0 = (1 - refraction_index) / (1 + refraction_index);
  r0 = r0 * r0;
  return r0 + (1 - r0) * static_cast<Float>(std::pow((1 - cosine), 5));
}
