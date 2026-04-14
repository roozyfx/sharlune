#ifndef INCLUDE_HITTABLES_H_
#define INCLUDE_HITTABLES_H_
#include <memory>
#include <vector>

#include "hit_record.h"
#include "hittable.h"
#include "interval.h"

/* A utility class for a colllection of hittable items */
using std::shared_ptr;
class Hittables {
  std::vector<shared_ptr<Hittable>> hittables_{};

 public:
  Hittables() : hittables_{} {}
  explicit Hittables(const std::vector<shared_ptr<Hittable>> &hittables)
      : hittables_{hittables} {}

  void add(const shared_ptr<Hittable> &h) { hittables_.push_back(h); }
  void clear() { hittables_.clear(); }

  /*
An extremely inefficient solution to find the Ray r, intersection with the
nearest object (Hittble) in our list
*/
  // TODO Not a good name, find a better one.
  bool hit_all(const Ray &r, Interval tt, HitRecord &record) {
    HitRecord temp_record;
    bool hit_anything{false};
    auto closest_sofar{tt.t_max};

    for (const auto &htbl : hittables_) {
      if (hit(*htbl, r, Interval(tt.t_min, closest_sofar), temp_record)) {
        hit_anything = true;
        closest_sofar = temp_record.t;
        record = temp_record;
      }
    }
    return hit_anything;
  }
};

#endif  // INCLUDE_HITTABLES_H_