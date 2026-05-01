#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

#include <memory>

template <typename T>
using Ptr = std::shared_ptr<T>;

template <typename T>
using UPtr = std::unique_ptr<T>;

#endif  // INCLUDE_TYPES_H_
