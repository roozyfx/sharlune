set(MY_RAYTRACER fx_tracer)

add_executable(${MY_RAYTRACER})
target_sources(${MY_RAYTRACER} PRIVATE "main.cpp")
target_compile_options(${MY_RAYTRACER} PRIVATE 
    -Wall -Wextra -Wpedantic
    $<$<CONFIG:Debug>:-g;-O0;-fsanitize=address,undefined;-Wfloat-equal;-fno-omit-frame-pointer>
    $<$<CONFIG:Release>:-O3;-march=native;-DNDEBUG>)

target_include_directories(${MY_RAYTRACER} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${MY_RAYTRACER} PRIVATE fx_tracer_lib)
target_link_options(${MY_RAYTRACER} PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)
