set(EXECUTABLE sharlune)

set(src_files
    "main.cpp"
    )

add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE} PRIVATE ${src_files})

# Copy configuration file to build directory
# To ensure copy, first create a dedicated target JUST for copying the config file
add_custom_target(CopyConfig
    # Ensure the destination folder exists BEFORE copying (crucial for clean builds)
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${EXECUTABLE}>"
    
    # Copy the file.
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/configuration.toml"
        "$<TARGET_FILE_DIR:${EXECUTABLE}>/configuration.toml"
    COMMENT "Synchronizing configuration.toml"
)
# make the main executable depend on CopyConfig
add_dependencies(${EXECUTABLE} CopyConfig)

# Linux and macOS Branch
if(CMAKE_SYSTEM_NAME MATCHES Linux)
    target_compile_options(${EXECUTABLE} PRIVATE
        $<$<CONFIG:Debug>:-g;-O0;-fsanitize=address,undefined;-Wfloat-equal;-fno-omit-frame-pointer>
        $<$<CONFIG:Release>:-O3;-march=native>
    )
    # GCC
    if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
        target_compile_options(${EXECUTABLE} PRIVATE
            -Wall -Wextra -Wpedantic
        )
    # Clang
    elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang OR CMAKE_CXX_COMPILER_ID MATCHES AppleClang)
        target_compile_options(${EXECUTABLE} PRIVATE
            -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-weak-vtables -Wno-c++20-extensions -Wno-padded
            # TODO remove and fix warnings
            -Wno-unsafe-buffer-usage
        )
    endif()
    target_link_options(${EXECUTABLE} PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
    )
    # Windows branch
elseif(CMAKE_SYSTEM_NAME MATCHES Windows)
    target_compile_options(${EXECUTABLE} PRIVATE
        /W4 /permissive-
        $<$<CONFIG:Debug>:/Od;/Zi;/fsanitize=address>
        $<$<CONFIG:Release>:/O2;/DNDEBUG>
    )

    target_link_options(${EXECUTABLE} PRIVATE
        # MSVC AddressSanitizer requires incremental linking to be disabled
        $<$<CONFIG:Debug>:/INCREMENTAL:NO>
    )
endif()

target_include_directories(${EXECUTABLE} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${EXECUTABLE} PRIVATE sharlune_raytracer_lib)

