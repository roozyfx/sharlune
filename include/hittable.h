#ifndef INCLUDE_HITTABLE_H_
#define INCLUDE_HITTABLE_H_
#include "details/shapeconcept.h"
#include "hit_record.h"

/*
Type Erasure pattern for a hittable shape
*/
class Hittable {
 public:
  template <typename GeometryT, typename HitStrategy>
  explicit Hittable(GeometryT geom, HitStrategy hs) {
    using Model = details::OwningHittableModel<GeometryT, HitStrategy>;
    pimple_ = std::make_unique<Model>(std::move(geom), std::move(hs));
  }

  Hittable(const Hittable& other) : pimple_{other.pimple_->clone()} {}
  Hittable& operator=(const Hittable& rhs) {
    Hittable copy(rhs);
    pimple_.swap(copy.pimple_);
    return *this;
  }

  Hittable(Hittable&&) = default;
  Hittable& operator=(Hittable&&) = default;
  ~Hittable() = default;

 private:
  std::unique_ptr<details::HittableConcept> pimple_;
  friend bool hit(const Hittable& geom, const Ray& r, const Interval& t,
                  HitRecord& record) {
    return geom.pimple_->hit(r, t, record);
  }
};

#endif  // INCLUDE_HITTABLE_H_
