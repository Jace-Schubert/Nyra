cmake_minimum_required(VERSION 3.21)

project(NyraRayTracer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(NyraRayTracer ${SOURCES})

target_include_directories(NyraRayTracer PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/vendor/glm
)

target_compile_definitions(NyraRayTracer PRIVATE
    GLM_FORCE_INTRINSICS
    GLM_FORCE_SSE2
    GLM_FORCE_ALIGNED_GENTYPES
    GLM_FORCE_INLINE
    GLM_FORCE_DEFAULT_PRECISION_HIGHP
)

target_compile_options(NyraRayTracer PRIVATE
    # --- General flags ---
    -Wall
    -Wextra
    -Wpedantic

    # --- Release flags ---
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Release>:-march=native>
    $<$<CONFIG:Release>:-ffast-math>
    $<$<CONFIG:Release>:-DNDEBUG>

    # --- Debug flags ---
    $<$<CONFIG:Debug>:-O0>
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Debug>:-fsanitize=address>
    $<$<CONFIG:Debug>:-fsanitize=undefined>
)

target_link_options(NyraRayTracer PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
    $<$<CONFIG:Debug>:-fsanitize=undefined>
)

target_precompile_headers(NyraRayTracer PRIVATE
    include/NyraPCH.h
)

add_subdirectory(vendor/glm)
target_link_libraries(NyraRayTracer PRIVATE glm::glm)