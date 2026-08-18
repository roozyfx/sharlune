#ifndef INCLUDE_HITTABLES_H_
#define INCLUDE_HITTABLES_H_
#include <vector>

#include "hit_record.h"
#include "interval.h"
#include "render_node.h"
#include "types.h"
/* A utility class for a collection of hittable items */
class RenderNodes {
  using NodePtr = UPtr<RenderNode>;
  using RenderNodesCollection = std::vector<NodePtr>;

  RenderNodesCollection render_nodes_{};

 public:
  RenderNodes() : render_nodes_{} {}

  inline void add(NodePtr&& h) { render_nodes_.push_back(std::move(h)); }
  inline void clear() { render_nodes_.clear(); }

  /*
  An extremely inefficient solution to find the Ray r, intersection with the
  nearest object (Hittable) in our list
  */
  // TODO Not a good name, find a better one.
  bool hit_all(const Ray& r, Interval tt, HitRecord& record) const;
};

#endif  // INCLUDE_HITTABLES_H_
