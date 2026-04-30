#ifndef INCLUDE_RENDER_H_
#define INCLUDE_RENDER_H_
#include <memory>

#include "camera.h"
#include "film.h"
#include "hittables.h"

void render(std::unique_ptr<Camera> camera, std::unique_ptr<Film> film,
            const std::shared_ptr<Hittables>& world);

#endif  // INCLUDE_RENDER_H_
