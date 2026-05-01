#ifndef INCLUDE_RENDER_H_
#define INCLUDE_RENDER_H_

#include "camera.h"
#include "film.h"
#include "render_nodes.h"
#include "types.h"

void render(UPtr<Camera> camera, UPtr<Film> film, Ptr<RenderNodes> world);

#endif  // INCLUDE_RENDER_H_
