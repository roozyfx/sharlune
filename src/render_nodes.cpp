#include "render_nodes.h"

bool RenderNodes::hit_all(const Ray &r, Interval tt, HitRecord &record) const {
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
