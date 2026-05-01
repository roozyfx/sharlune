#ifndef INCLUDE_SCATTER_H_
#define INCLUDE_SCATTER_H_

#include "hit_record.h"
#include "material.h"
#include "ray.h"
#include "rng.h"
#include "vectormath.h"

struct Scatter {
  bool operator()(const Metal &material, const Ray &in_ray,
                  const HitRecord &rec, Color &attenuation,
                  Ray &out_ray) const {
    Vec3 reflected = reflect(in_ray.direction(), rec.n);
    out_ray = Ray(rec.p, reflected);
    attenuation = material.albedo;

    return true;
  }

  bool operator()(const Lambertian &material, const Ray &, const HitRecord &rec,
                  Color &attenuation, Ray &out_ray) const {
    // TODO correct and complete lambertian
    auto scatter_direction = rec.n + random_unit_vector();
    out_ray = Ray(rec.p, scatter_direction);
    attenuation = material.albedo;

    return true;
  }
};

#endif  // INCLUDE_SCATTER_H_
