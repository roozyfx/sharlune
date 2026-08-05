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
    pimpl_ = std::make_unique<Model>(std::move(geom), std::move(hs));
  }

  Hittable(const Hittable& other) : pimpl_{other.pimpl_->clone()} {}
  Hittable& operator=(const Hittable& rhs) {
    Hittable copy(rhs);
    pimpl_.swap(copy.pimpl_);
    return *this;
  }

  Hittable(Hittable&&) = default;
  Hittable& operator=(Hittable&&) = default;
  ~Hittable() = default;

 private:
  std::unique_ptr<details::HittableConcept> pimpl_;
  friend bool hit(const Hittable& geom, const Ray& r, const Interval& t,
                  HitRecord& record) {
    return geom.pimpl_->hit(r, t, record);
  }
};

#endif  // INCLUDE_HITTABLE_H_
