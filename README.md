# Sharlune

A CPU-based ray tracer implemented in C++23.

## Overview

Sharlune is a study in modern C++ architecture.  
It follows Shirley/Black/Hollasch's Ray Tracing series in physics and rendering calculations ([1](https://raytracing.github.io/books/RayTracingInOneWeekend.html), [2](https://raytracing.github.io/books/RayTracingTheNextWeek.html)), but it deviates in the architecture, design and implementation by adapting modern C++ and benefiting from multiple design patterns (Type Erasure, Visitor, CRTP, ...). It is also multithreaded.  
It supports some basic geometries at the moment, OpenEXR format, lighting, shadows, and reflection. Although these features will extend gradually, the emphasis here is more on the architecture and utilizing modern C++ design.      
For more on the design choices and noteworthy implementation details, see [DESIGN.md](https://github.com/roozyfx/sharlune/blob/master/DESIGN.md).  
  

![sample render: Spheres](./gallery/exr2png_spheres.png "Spheres")  

## Features

- Ray tracing renderer
- Support for spheres and planes
- Basic lighting and shadows
- Image output formats:  
    - OpenEXR's exr  
    - ppm

## Dependencies

If you choose an .exr format:  
- OpenEXR (https://openexr.com/en/latest/)  

Internet connection to fetch Tomlplusplus
- tomlplusplus (https://github.com/marzer/tomlplusplus)

## Build

Use your preferred C/C++ compiler with support for C++23 features. For example:

```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

## Run

Run the generated executable and save the rendered image:
Change settings in `configuration.toml` to your liking and run: 
```bash
./sharlune
```
