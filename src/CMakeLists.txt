set(PROJECT_LIBRARY_NAME sharlune_raytracer_lib)

find_package(Threads REQUIRED)

set(src
  configuration.cpp
  hit_strategies.cpp
  interval.cpp
  material.cpp
  pinhole_camera.cpp
  ppm.cpp 
  render.cpp
  render_nodes.cpp
  rng.cpp
  scatter.cpp
  scene.cpp
)

add_library(${PROJECT_LIBRARY_NAME} STATIC ${src})

target_include_directories(${PROJECT_LIBRARY_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/3rdParty)
target_include_directories(${PROJECT_LIBRARY_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

# ---------------------------------------------------------------------------
# gcc and Clang (GCC and Clang compilers)
# ---------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_LIBRARY_NAME} PRIVATE
        -Wall -Wextra -Wpedantic
        $<$<CONFIG:Debug>:-g;-O0;-fsanitize=address,undefined;-Wfloat-equal;-fno-omit-frame-pointer>
        $<$<CONFIG:Release>:-O3;-march=native;-DNDEBUG>
    )
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(${PROJECT_LIBRARY_NAME} PRIVATE
      -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-weak-vtables -Wno-c++20-extensions -Wno-padded
      # TODO remove and fix warnings
    -Wno-unsafe-buffer-usage
      $<$<CONFIG:Debug>:-g;-O0;-fsanitize=address,undefined;-Wfloat-equal;-fno-omit-frame-pointer>
      $<$<CONFIG:Release>:-O3;-march=native;-DNDEBUG>
  )
  endif()
      
    target_link_options(${PROJECT_LIBRARY_NAME} PUBLIC
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
    )
# ---------------------------------------------------------------------------
# MSVC (Microsoft Visual C++)
# ---------------------------------------------------------------------------
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_LIBRARY_NAME} PRIVATE
        /W4 /permissive-
        $<$<CONFIG:Debug>:/Od;/Zi;/fsanitize=address>
        $<$<CONFIG:Release>:/O2;/DNDEBUG>
    )
      
    target_link_options(${PROJECT_LIBRARY_NAME} PUBLIC
        # MSVC AddressSanitizer requires incremental linking to be disabled
        $<$<CONFIG:Debug>:/INCREMENTAL:NO>
    )
endif()

target_link_libraries(${PROJECT_LIBRARY_NAME} PUBLIC Threads::Threads tomlplusplus::tomlplusplus)

target_compile_definitions(${PROJECT_LIBRARY_NAME} PRIVATE 
    $<$<CONFIG:Release>:PARALLEL>
)
target_link_libraries(${PROJECT_LIBRARY_NAME} PRIVATE $<$<CONFIG:Release>:tbb>)
