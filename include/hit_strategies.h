#ifndef INCLUDE_HIT_STRATEGIES_H_
#define INCLUDE_HIT_STRATEGIES_H_

class Sphere;
class Cube;
class Cylinder;
class Ray;
struct HitRecord;
struct Interval;

bool hit_sphere(const Sphere& s, const Ray& r, const Interval& t,
                HitRecord& record);

bool hit_cube(const Cube& c, const Ray& r, const Interval& t,
              HitRecord& record);

bool hit_cylinder(const Cylinder& c, const Ray& r, const Interval& t,
                  HitRecord& record);

class HitStrategy {
 public:
  bool operator()(const Sphere& s, const Ray& r, const Interval& t,
                  HitRecord& record) const {
    return hit_sphere(s, r, t, record);
  }

  bool operator()(const Cube& c, const Ray& r, const Interval& t,
                  HitRecord& record) const {
    return hit_cube(c, r, t, record);
  }

  bool operator()(const Cylinder& c, const Ray& r, const Interval& t,
                  HitRecord& record) const {
    return hit_cylinder(c, r, t, record);
  }
};

#endif  // INCLUDE_HIT_STRATEGIES_H_
