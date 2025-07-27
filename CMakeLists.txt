cmake_minimum_required(VERSION 3.21)

project(tincture)

set(CMAKE_CXX_STANDARD 20)

set(SPIRV_SKIP_EXECUTABLES ON CACHE BOOL "")

add_subdirectory(SPIRV-Headers)
add_subdirectory(SPIRV-Tools)

file(GLOB_RECURSE TINT_SOURCES "${PROJECT_SOURCE_DIR}/tint/src/*.cc")

add_library(tint SHARED)
target_sources(tint PRIVATE ${TINT_SOURCES})
target_include_directories(tint PUBLIC "${PROJECT_SOURCE_DIR}/tint")
target_include_directories(tint PRIVATE "${PROJECT_SOURCE_DIR}/SPIRV-Tools")
target_include_directories(tint PRIVATE "${PROJECT_BINARY_DIR}/SPIRV-Tools")
target_compile_definitions(tint PUBLIC TINT_BUILD_SPV_READER TINT_BUILD_WGSL_WRITER)
target_link_libraries(tint PRIVATE SPIRV-Headers SPIRV-Tools SPIRV-Tools-opt)

add_library(tincture tincture.cpp)
target_include_directories(tincture PUBLIC "${PROJECT_SOURCE_DIR}/tint/include")
target_link_libraries(tincture PRIVATE tint)

if(PROJECT_IS_TOP_LEVEL)
  add_executable(example example.c)
  target_link_libraries(example tincture)
  if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_libraries(example "-sSTACK_SIZE=262144")
  endif()
endif()
