cmake_minimum_required(VERSION 3.28...4.4)
project(sharlune         
        VERSION 0.2.0
        DESCRIPTION "Sharlune: Multi-threaded Rendering Engine, A Modern C++ Architecture Study"
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
