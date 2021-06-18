cmake_minimum_required(VERSION 3.18)
project(GoL)

set(CMAKE_CXX_STANDARD 20)

message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")

add_executable(GoL
        conf.hpp
        main.cpp

        Core/Core.hpp
        Core/Core.cpp
        Core/inputs.cpp
        Core/utils.cpp
)

find_package(Threads)
target_link_libraries(GoL ${CMAKE_THREAD_LIBS_INIT})

find_package(SFML 2.5 REQUIRED audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(GoL sfml-graphics sfml-audio sfml-system sfml-window)
