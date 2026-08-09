[![Multi-platform CMake Build (Linux(gcc/clang), macOS, Windows)](https://github.com/roozyfx/sharlune/actions/workflows/cmake_multi-platform.yml/badge.svg)](https://github.com/roozyfx/sharlune/actions/workflows/cmake_multi-platform.yml)  ![C++23](extra/C%2B%2B-23-blue.svg?style=flat&logo=c%2B%2B&logoColor=white)

# Sharlune

A CPU-based ray tracer implemented in C++23.

## Overview

Sharlune is a study in modern C++ architecture.  
It follows Shirley/Black/Hollasch's Ray Tracing series in physics and rendering calculations ([1](https://raytracing.github.io/books/RayTracingInOneWeekend.html), [2](https://raytracing.github.io/books/RayTracingTheNextWeek.html)), but it deviates in the architecture, design and implementation by adapting modern C++ and benefiting from multiple design patterns (Type Erasure, Visitor, CRTP, ...). It is also multithreaded.  
It supports some basic geometries at the moment, OpenEXR format, lighting, shadows, and reflection. Although these features will extend gradually, the emphasis here is more on the architecture and utilizing modern C++ design.      
For more on the design choices and noteworthy implementation details, see [DESIGN.md](DESIGN.md).  
  

![sample render: Spheres](./gallery/exr2png_spheres.png "Spheres")  

## Features

- Ray tracing renderer
- Support for spheres, cubes, cylinders
- Basic lighting and shadows
- Image output formats:  
    - OpenEXR's exr  
    - ppm

## Dependencies

If you choose an .exr format:  
- OpenEXR (https://openexr.com/en/latest/)  

Internet connection to fetch Tomlplusplus
- tomlplusplus (https://github.com/marzer/tomlplusplus)

Google Test (https://github.com/google/googletest)  

## Build

Use your preferred C/C++ compiler with support for C++23 features. For example:

```bash
mkdir -p build
```
list available presets on your platform and choose one `cmake --list-presets`  

```   
cmake --preset <preset> ..
cd build/<preset>
cmake --build . --config <Release|Debug> --target sharlune --
```

## Run

Run the generated executable and save the rendered image:
Change settings in `configuration.toml` to your liking and run: 
```bash
./sharlune
```
