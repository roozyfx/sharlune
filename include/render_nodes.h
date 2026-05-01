#ifndef INCLUDE_HITTABLES_H_
#define INCLUDE_HITTABLES_H_
#include <vector>

#include "hit_record.h"
#include "hittable.h"
#include "interval.h"
#include "render_node.h"
#include "types.h"
/* A utility class for a colllection of hittable items */
class RenderNodes {
  using NodePtr = UPtr<RenderNode>;
  using RenderNodesCollection = std::vector<NodePtr>;

  RenderNodesCollection render_nodes_{};

 public:
  RenderNodes() : render_nodes_{} {}
  // explicit RenderNodes(RenderNodesCollection nodes)
  //     : render_nodes_{std::move(nodes)} {}

  void add(NodePtr &&h) { render_nodes_.push_back(std::move(h)); }
  void clear() { render_nodes_.clear(); }

  /*
  An extremely inefficient solution to find the Ray r, intersection with the
  nearest object (Hittble) in our list
  */
  // TODO Not a good name, find a better one.
  bool hit_all(const Ray &r, Interval tt, HitRecord &record) const {
    HitRecord temp_record;
    bool hit_anything{false};
    auto closest_sofar{tt.max};

    for (const auto &node : render_nodes_) {
      if (node && hit(node->geometry(), r, Interval(tt.min, closest_sofar),
                      temp_record)) {
        hit_anything = true;
        closest_sofar = temp_record.t;
        record = temp_record;
        record.material = node->material();
      }
    }
    return hit_anything;
  }
};

#endif  // INCLUDE_HITTABLES_H_
