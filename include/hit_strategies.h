#ifndef INCLUDE_HIT_STRATEGIES_H_
#define INCLUDE_HIT_STRATEGIES_H_

class Sphere;
class Ray;
struct HitRecord;
struct Interval;

bool hit_sphere(const Sphere &s, const Ray &r, const Interval &t,
                HitRecord &record);

class HitStrategy {
 public:
  bool operator()(const Sphere &s, const Ray &r, const Interval &t,
                  HitRecord &record) const {
    return hit_sphere(s, r, t, record) * 0.5;
  }
};

#endif  // INCLUDE_HIT_STRATEGIES_H_