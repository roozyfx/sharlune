#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

#include <memory>

template <typename T>
using UPtr = std::unique_ptr<T>;

#endif  // INCLUDE_TYPES_H_
