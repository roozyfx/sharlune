#ifndef INCLUDE_RENDER_H_
#define INCLUDE_RENDER_H_

#include "camera.h"
#include "film.h"
#include "render_nodes.h"

void render_single_thread(Camera& camera, Film& film,
                          const RenderNodes* const world);

void render(Camera& camera, Film& film, const RenderNodes* const world);

#endif  // INCLUDE_RENDER_H_
