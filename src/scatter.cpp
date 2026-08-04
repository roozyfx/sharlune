#include "scatter.h"

#include "material.h"
#include "rng.h"
#include "vectormath.h"

bool Scatter::operator()(const Metal& material, const Ray& in_ray,
                         const HitRecord& rec, Color& attenuation,
                         Ray& out_ray) const {
  Vec3 reflected = reflect(in_ray.direction(), rec.n);
  reflected = normalize(reflected) + (material.fuzz * random_unit_vector());
  out_ray = Ray(rec.p, reflected);
  attenuation = material.albedo;

  return dot(out_ray.direction(), rec.n) > Float(0);
}

bool Scatter::operator()(const Lambertian& material, const Ray&,
                         const HitRecord& rec, Color& attenuation,
                         Ray& out_ray) const {
  auto scatter_direction = rec.n + random_unit_vector();
  if (near_zero(scatter_direction)) {
    scatter_direction = rec.n;
  }
  out_ray = Ray(rec.p, scatter_direction);
  attenuation = material.albedo;

  return true;
}

bool Scatter::operator()(const Dielectric& material, const Ray& in_ray,
                         const HitRecord& rec, Color& attenuation,
                         Ray& out_ray) const {
  attenuation = material.albedo;
  const Float ri{rec.front_face ? (Float(1) / material.refraction_index)
                                : material.refraction_index};

  Vec3 unit_direction = normalize(in_ray.direction());
  const Float cos_theta{std::min(dot(-unit_direction, rec.n), Float(1))};
  const Float sin_theta{std::sqrt(Float(1) - cos_theta * cos_theta)};

  const bool cannot_refract{ri * sin_theta > Float(1)};
  Vec3 direction;

  direction = (cannot_refract ||
               Dielectric::reflectance(cos_theta, ri) > random_number())
                  ? reflect(unit_direction, rec.n)
                  : refract(unit_direction, rec.n, ri);

  out_ray = Ray(rec.p, direction);

  return true;
}
