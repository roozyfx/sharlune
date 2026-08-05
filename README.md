# Sharlune

A CPU-based ray tracer implemented in C++23.

## Overview

Sharlune is ray tracer that renders 3D scenes using ray-object intersections, lighting, shadows, and reflection.    
It follows [Shirley](https://github.com/petershirley), [Black](https://github.com/trevordblack) and [Hollasch](https://github.com/hollasch) Ray Tracing series in physics and rendering calculations ([_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html), [_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html)), but it deviates in the implementation by adapting a different architecture and benefiting from multiple design patterns (CRTP, Visitor, Type Erasure, ...).  
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
