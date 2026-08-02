include(FetchContent)
# Fetch Toml++ into the build directory
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)


# Fetch TinyEXR into the build directory and treat its include paths 
# as system headers to suppress include warnings.
FetchContent_Declare(
    tinyexr
    URL https://github.com/syoyo/tinyexr/archive/refs/tags/v3.2.0.zip
    SYSTEM
    EXCLUDE_FROM_ALL
)

# Prevent building sample
set(TINYEXR_BUILD_SAMPLE OFF CACHE BOOL "Disable TinyEXR samples" FORCE)

FetchContent_MakeAvailable(tinyexr)

# Suppress warnings when compiling TinyEXR
if(TARGET tinyexr)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(tinyexr PRIVATE -w)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        target_compile_options(tinyexr PRIVATE /W0)
    endif()
endif()