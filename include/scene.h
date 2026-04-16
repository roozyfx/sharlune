#ifndef INCLUDE_SCENE_H_
#define INCLUDE_SCENE_H_

#include <memory>

#include "hittables.h"

std::shared_ptr<Hittables> create_world();

#endif