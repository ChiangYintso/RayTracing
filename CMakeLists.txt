cmake_minimum_required(VERSION 3.16.4)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE RAY_TRACING_SRC src/*.cpp)
add_library(ray_tracing ${RAY_TRACING_SRC})
target_include_directories(ray_tracing PUBLIC include)

# add binary executables
file(GLOB BIN_SOURCES "${PROJECT_SOURCE_DIR}/bin/*.cpp")

foreach(bin_source ${BIN_SOURCES})
    get_filename_component(bin_source_filename ${bin_source} NAME)
    string(REPLACE ".cpp" "" bin_source_name ${bin_source_filename})
    add_executable(${bin_source_name} ${bin_source})
    target_include_directories(${bin_source_name} PUBLIC include)
    target_link_libraries(${bin_source_name} ray_tracing)
endforeach(bin_source ${BIN_SOURCES})