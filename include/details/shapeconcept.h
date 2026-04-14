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

template <typename GeometryT, typename HitStrategy>
class OwningHittableModel : public HittableConcept {
 public:
  explicit OwningHittableModel(GeometryT geom, HitStrategy hs)
      : geometry_(std::move(geom)), hit_strategy_(std::move(hs)) {}

  bool hit(const Ray &r, const Interval &t, HitRecord &record) const override {
    return hit_strategy_(geometry_, r, t, record);
  }

  std::unique_ptr<HittableConcept> clone() const override {
    return std::make_unique<OwningHittableModel>(*this);
  }

 private:
  GeometryT geometry_;
  HitStrategy hit_strategy_;
};
}  // namespace details

#endif  // INCLUDE_DETAILS_SHAPECONCEPT_H_