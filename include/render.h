#ifndef INCLUDE_RENDER_H_
#define INCLUDE_RENDER_H_
#include <functional>
#include <memory>

#include "camera.h"
#include "film.h"
#include "hittables.h"
#include "ray.h"
#include "vectormath.h"

using ColorFunction = std::function<Color(
    const Ray& r, std::shared_ptr<Hittables> world, size_t depth)>;

void render(std::unique_ptr<Camera> camera, std::unique_ptr<Film> film,
            const std::shared_ptr<Hittables>& world,
            ColorFunction color_function);

#endif  // INCLUDE_RENDER_H_
