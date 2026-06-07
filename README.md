# Sharlune

A CPU-based ray tracer implemented in C++23.

## Overview

This repository contains a basic ray tracing project that renders 3D scenes using ray-object intersections, lighting, shadows, and reflection.

## Features

- Ray tracing renderer
- Support for spheres and planes
- Basic lighting and shadows
- Image output only in PPM format at the moment

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

```bash
./sharlune
```
