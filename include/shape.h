#ifndef INCLUDE_SHAPE_H_
#define INCLUDE_SHAPE_H_
#include "details/shapeconcept.h"
#include "hit_record.h"

/*
Type Erasure pattern for a hittable shape
*/
class Shape {
 public:
  template <typename ShapeT, typename HitStrategy>
  explicit Shape(ShapeT shape, HitStrategy hs) {
    using Model = details::OwningHittableModel<ShapeT, HitStrategy>;
    pimple_ = std::make_unique<Model>(std::move(shape), std::move(hs));
  }

  Shape(const Shape &other) : pimple_{other.pimple_->clone()} {}
  Shape &operator=(const Shape &rhs) {
    Shape copy(rhs);
    pimple_.swap(copy.pimple_);
    return *this;
  }

  Shape(Shape &&) = default;
  Shape &operator=(Shape &&) = default;
  ~Shape() = default;

 private:
  std::unique_ptr<details::HittableConcept> pimple_;
  friend bool hit(const Shape &shape, const Ray &r, const Interval &t,
                  HitRecord &record) {
    return shape.pimple_->hit(r, t, record);
  }
};

#endif  // INCLUDE_SHAPE_H_
