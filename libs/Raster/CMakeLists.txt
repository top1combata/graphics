cmake_minimum_required(VERSION 3.21)

set(PROJECT_NAME Raster)

set(SOURCES 
    include/Raster.h
    src/Raster.cpp
    src/Primitives.cpp
    src/Polygon.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)


add_subdirectory(SFML)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)