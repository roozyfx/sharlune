#include <memory>

#include "basic_geometries.h"
#include "hit_strategies.h"
#include "hittable.h"
#include "material.h"
#include "render_node.h"
#include "render_nodes.h"
#include "scene.h"
#include "vectormath.h"

UPtr<RenderNodes> create_world() {
  // Create some spheres, other objects
  Sphere sphere1(Point3(0, 0, -1), .500);
  Hittable object1(sphere1, HitStrategy());
  RenderNode node1(std::move(object1), Lambertian(Color(200, 0, 3)));

  Sphere sphere2(Point3(1, 2, -3), 0.4);
  Hittable object2(sphere2, hit_sphere);
  RenderNode node2(std::move(object2), Metal{Color(100, 200, 300)});

  Cube cube1(Point3(-2., -1., -2.), .6);
  Hittable object3(cube1, hit_cube);
  RenderNode node3(std::move(object3), Lambertian{Color(0, 100, 300)});

  // Add objects to to the scene
  UPtr<RenderNodes> world = std::make_unique<RenderNodes>();
  world->add(std::make_unique<RenderNode>(node1));
  world->add(std::make_unique<RenderNode>(node2));
  world->add(std::make_unique<RenderNode>(node3));

  return world;
}
