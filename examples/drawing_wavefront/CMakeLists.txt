cmake_minimum_required(VERSION 3.21)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(SOURCES 
    main.cpp
    parse.h
    parse.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})