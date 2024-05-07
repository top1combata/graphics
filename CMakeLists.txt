cmake_minimum_required(VERSION 3.21)

project(graphics)

set(CMAKE_CXX_STANDARD 20)

if (NOT ${CMAKE_BUILD_TYPE} STREQUAL debug) 
    set(CMAKE_CXX_FLAGS "-O2 -march=native")
endif()

add_subdirectory(libs/Raster)

file(GLOB dirs examples/*)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

foreach(dir ${dirs})
    get_filename_component(dir ${dir} NAME)

    add_subdirectory(examples/${dir})
    target_link_libraries(${dir} Raster)
endforeach()