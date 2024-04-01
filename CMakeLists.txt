cmake_minimum_required(VERSION 3.21)

project(graphics)

if (NOT ${CMAKE_BUILD_TYPE} STREQUAL debug) 
    set(CMAKE_CXX_FLAGS "-O2 -march=native")
endif()

add_subdirectory(libs/Raster)

add_subdirectory(line_circle)
target_link_libraries(line_circle Raster)

add_subdirectory(polygon)
target_link_libraries(polygon Raster)