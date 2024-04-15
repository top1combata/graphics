cmake_minimum_required(VERSION 3.21)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(SOURCES
    main.cpp
    algorithms.h
    algorithms.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})