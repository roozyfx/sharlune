cmake_minimum_required(VERSION 3.25..4.4)
project(fx_tracer         
        VERSION 0.1.0
        DESCRIPTION "Learning simple Ray Tracer in C++"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions("DEBUG")
endif()

# Options
option(BUILD_TESTING "Build tests" ON)
option(BUILD_BENCHMARK "Build benchmarks" ON)

add_subdirectory(3rdParty)
add_subdirectory(src)
add_subdirectory(app)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests) 
endif()
if(BUILD_BENCHMARK)
  add_subdirectory(benchmark)
endif()
