#include "rng.h"
#include "scatter.h"

bool Scatter::operator()(const Metal &material, const Ray &in_ray,
                         const HitRecord &rec, Color &attenuation,
                         Ray &out_ray) const {
  Vec3 reflected = reflect(in_ray.direction(), rec.n);
  reflected = normalize(reflected) + (material.fuzz * random_unit_vector());
  out_ray = Ray(rec.p, reflected);
  attenuation = material.albedo;

  return dot(out_ray.direction(), rec.n) > Float(0);
}

bool Scatter::operator()(const Lambertian &material, const Ray &,
                         const HitRecord &rec, Color &attenuation,
                         Ray &out_ray) const {
  auto scatter_direction = rec.n + random_unit_vector();
  if (near_zero(scatter_direction)) {
    scatter_direction = rec.n;
  }
  out_ray = Ray(rec.p, scatter_direction);
  attenuation = material.albedo;

  return true;
}