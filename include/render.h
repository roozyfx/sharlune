#ifndef INCLUDE_RENDER_H_
#define INCLUDE_RENDER_H_
#include <memory>

#include "camera.h"
#include "film.h"
#include "types.h"

void render(UPtr<Camera> camera, UPtr<Film> film,
            const std::shared_ptr<Hittables>& world);

#endif  // INCLUDE_RENDER_H_
