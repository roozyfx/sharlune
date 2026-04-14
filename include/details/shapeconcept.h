#ifndef INCLUDE_DETAILS_SHAPECONCEPT_H_
#define INCLUDE_DETAILS_SHAPECONCEPT_H_
#include <memory>

class Ray;
struct HitRecord;
struct Interval;

/*
Details for the Type Erasure pattern
*/
namespace details {
class HittableConcept {
 public:
  virtual ~HittableConcept() = default;
  virtual bool hit(const Ray &, const Interval &t, HitRecord &record) const = 0;
  virtual std::unique_ptr<HittableConcept> clone() const = 0;
};

template <typename ShapeT, typename HitStrategy>
class OwningHittableModel : public HittableConcept {
 public:
  explicit OwningHittableModel(ShapeT shape, HitStrategy hs)
      : shape_(std::move(shape)), hitst_(std::move(hs)) {}

  bool hit(const Ray &r, const Interval &t, HitRecord &record) const override {
    return hitst_(shape_, r, t, record);
  }

  std::unique_ptr<HittableConcept> clone() const override {
    return std::make_unique<OwningHittableModel>(*this);
  }

 private:
  ShapeT shape_;
  HitStrategy hitst_;
};
}  // namespace details

#endif  // INCLUDE_DETAILS_SHAPECONCEPT_H_