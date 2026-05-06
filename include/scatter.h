#ifndef INCLUDE_SCATTER_H_
#define INCLUDE_SCATTER_H_

#include "hit_record.h"
#include "material.h"
#include "ray.h"
#include "vectormath.h"

struct Scatter {
  bool operator()(const Metal &material, const Ray &in_ray,
                  const HitRecord &rec, Color &attenuation, Ray &out_ray) const;

  bool operator()(const Lambertian &material, const Ray &, const HitRecord &rec,
                  Color &attenuation, Ray &out_ray) const;
};

#endif  // INCLUDE_SCATTER_H_
