#ifndef INCLUDE_RENDER_NODE_H_
#define INCLUDE_RENDER_NODE_H_

#include "hittable.h"
#include "material.h"

class RenderNode {
  Hittable geometry_;
  Material material_;

 public:
  explicit RenderNode(Hittable&& geom, Material mat)
      : geometry_(std::move(geom)), material_(mat) {}

  inline Hittable geometry() const { return geometry_; }
  inline Material material() const { return material_; }
};

#endif  // INCLUDE_RENDER_NODE_H_
