#ifndef INCLUDE_COLOR_FUNCTIONS_H_
#define INCLUDE_COLOR_FUNCTIONS_H_
#include <memory>

#include "hittables.h"
#include "ray.h"
#include "vectormath.h"

Color sample_colorize(const Ray& r, const std::shared_ptr<Hittables>& world,
                      size_t depth);
Color naive_diffuse(const Ray& r, const std::shared_ptr<Hittables>& world,
                    size_t depth);
Color lambertian_diffuse(const Ray& r, const std::shared_ptr<Hittables>& world,
                         size_t depth);
#endif  // INCLUDE_COLOR_FUNCTIONS_H_
