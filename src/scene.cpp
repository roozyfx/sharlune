#include "basic_geometries.h"
#include "hit_strategies.h"
#include "scene.h"

std::shared_ptr<Hittables> create_world() {
  // Create some spheres, other objects
  Sphere sphere1(Point3(0, 0, -1), 0.5);
  Hittable object1(sphere1, HitStrategy());
  Sphere sphere2(Point3(1, 3, -3), 0.4);
  Hittable object2(sphere2, hit_sphere);

  // Add objects to to the scene

  std::shared_ptr<Hittables> world = std::make_shared<Hittables>();
  world->add(std::make_shared<Hittable>(object1));
  world->add(std::make_shared<Hittable>(object2));

  return world;
}