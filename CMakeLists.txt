cmake_minimum_required(VERSION 3.16.4)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)
if (LINUX)
    # valgrind
    find_program(VALGRIND_BIN valgrind)
    if ("${VALGRIND_BIN}" STREQUAL "VALGRIND_BIN-NOTFOUND")
        message(WARNING "RayTracing Test couldn't find valgrind.")
    else ()
        message(STATUS "RayTracing Test found valgrind at ${VALGRIND_BIN}")
    endif ()

    set(VALGRIND_OPTIONS
            --error-exitcode=1                      # if leaks are detected, return nonzero value
            # --gen-suppressions=all  # uncomment for leak suppression syntax
            --leak-check=full                       # detailed leak information
            --soname-synonyms=somalloc=*jemalloc*   # also intercept jemalloc
            --trace-children=yes                    # trace child processes
            --track-origins=yes                     # track origin of uninitialized values
            )
endif (LINUX)

enable_testing()
include(CTest)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://hub.fastgit.org/google/googletest.git
        GIT_TAG release-1.10.0
        GIT_SHALLOW TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(install_gtest OFF)
set(install_gmock OFF)
FetchContent_MakeAvailable(googletest)

# stb_image
file(DOWNLOAD https://cdn.jsdelivr.net/gh/nothings/stb@master/stb_image.h
        ${CMAKE_SOURCE_DIR}/thirdparty/stb_image.h)
file(DOWNLOAD https://cdn.jsdelivr.net/gh/nothings/stb@master/stb_image_write.h
        ${CMAKE_SOURCE_DIR}/thirdparty/stb_image_write.h)


file(GLOB_RECURSE RAY_TRACING_SOURCES src/*.cpp)

foreach (ray_tracing_src ${RAY_TRACING_SOURCES})
    if (${ray_tracing_src} MATCHES ^.*_test\\.cpp$)
        # Create a human readable name.
        get_filename_component(ray_tracing_test_filename ${ray_tracing_src} NAME)
        string(REPLACE ".cpp" "" ray_tracing_test_name ${ray_tracing_test_filename})

        add_executable(${ray_tracing_test_name} ${ray_tracing_src})
        target_link_libraries(${ray_tracing_test_name} ray_tracing gtest_main)

        # Add the test under CTest.
        if (LINUX)
            add_test(NAME ${ray_tracing_test_name}_valgrind COMMAND ${VALGRIND_BIN} ${VALGRIND_OPTIONS} ${ray_tracing_test_name})
        endif (LINUX)
        add_test(NAME ${ray_tracing_test_name} COMMAND ${ray_tracing_test_name})
    else ()
        list(APPEND RAY_TRACING_SOURCE_FILES ${ray_tracing_src})
    endif (${ray_tracing_src} MATCHES ^.*_test\\.cpp$)
endforeach (ray_tracing_src ${RAY_TRACING_SOURCES})

add_library(ray_tracing ${RAY_TRACING_SOURCE_FILES})
target_include_directories(ray_tracing PUBLIC thirdparty)
target_include_directories(ray_tracing PUBLIC include)

# add binary executables
file(GLOB BIN_SOURCES "${PROJECT_SOURCE_DIR}/bin/*.cpp")

foreach (bin_source ${BIN_SOURCES})
    get_filename_component(bin_source_filename ${bin_source} NAME)
    string(REPLACE ".cpp" "" bin_source_name ${bin_source_filename})
    add_executable(${bin_source_name} ${bin_source})
    target_include_directories(${bin_source_name} PUBLIC include)
    target_link_libraries(${bin_source_name} ray_tracing)
endforeach (bin_source ${BIN_SOURCES})