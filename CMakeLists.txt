cmake_minimum_required(VERSION 3.21)

add_subdirectory(libs/Raster)

add_subdirectory(line_circle)
target_link_libraries(line_circle Raster)