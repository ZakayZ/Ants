cmake_minimum_required(VERSION 3.21)
project(Ants)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(Sources
        Utils/RandomGenerator.cpp
        States/AntState.cpp
        World/Sensor.cpp
        Ants/Ant.cpp
        World/PheromoneMap.cpp
        World/Colony.cpp
        World/World.cpp
        Renderer/Renderer.cpp
        App.cpp)

add_executable(Ants ${Sources} main.cpp)

target_include_directories(Ants PUBLIC .)

target_include_directories(Ants PUBLIC ../Geometry/GeometryEntities)

target_link_libraries(Ants sfml-graphics)