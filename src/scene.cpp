#include "scene.h"

#include <memory>

#include "basic_geometries.h"
#include "hit_strategies.h"
#include "hittable.h"
#include "material.h"
#include "render_node.h"
#include "render_nodes.h"
#include "vectormath.h"

UPtr<RenderNodes> create_world() {
  auto material_ground = Lambertian(Color(0.8, 0.8, 0.0) * 255);
  auto material_center = Lambertian(Color(0.1, 0.2, 0.5) * 255);
  auto material_left = Metal(Color(0.8, 0.8, 0.8) * 255, 0.3);
  auto material_right = Metal(Color(0.8, 0.6, 0.2) * 255, 0);

  Sphere sphere1(Point3(0.0, -100.5, -1.0), 100.0);
  Sphere sphere2(Point3(0.0, 0.0, -1.2), 0.5);
  Sphere sphere3(Point3(-1.0, 0.0, -1.0), 0.5);
  Sphere sphere4(Point3(1.0, 0.0, -1.0), 0.5);
  Hittable object1(sphere1, HitStrategy());
  Hittable object2(sphere2, HitStrategy());
  Hittable object3(sphere3, HitStrategy());
  Hittable object4(sphere4, HitStrategy());

  RenderNode node1(std::move(object1), material_ground);
  RenderNode node2(std::move(object2), material_center);
  RenderNode node3(std::move(object3), material_left);
  RenderNode node4(std::move(object4), material_right);

  // Create some spheres, other objects
  // Sphere sphere1(Point3(0, 0, -1), .500);
  // Hittable object1(sphere1, HitStrategy());
  // RenderNode node1(std::move(object1), Lambertian(Color(177, 186, 54)));

  // Sphere sphere2(Point3(1, 2, -3), 0.4);
  // Hittable object2(sphere2, hit_sphere);
  // RenderNode node2(std::move(object2), Metal{Color(250, 10, 100), .2});

  // Cube cube1(Point3(-2., -1., -2.), .6);
  // Hittable object3(cube1, hit_cube);
  // RenderNode node3(std::move(object3), Metal{Color(0, 0, 200), .3});

  // Add objects to to the scene
  UPtr<RenderNodes> world = std::make_unique<RenderNodes>();
  world->add(std::make_unique<RenderNode>(node1));
  world->add(std::make_unique<RenderNode>(node2));
  world->add(std::make_unique<RenderNode>(node3));
  world->add(std::make_unique<RenderNode>(node4));

  return world;
}
