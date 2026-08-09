cmake_minimum_required(VERSION 3.28...4.4)
project(sharlune         
        VERSION 0.3.0
        DESCRIPTION "Sharlune: Multi-threaded Rendering Engine, A Modern C++ Architecture Study"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(BUILD_BENCHMARK "Build benchmarks" ON)

add_subdirectory(3rdParty)
add_subdirectory(src)
add_subdirectory(app)

include(CTest)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests) 
endif()
if(BUILD_BENCHMARK)
  add_subdirectory(benchmark)
endif()
