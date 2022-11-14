cmake_minimum_required(VERSION 3.21)
project(Ants)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Werror")

set(CMAKE_CXX_STANDARD 20)

set(Sources
        Utils/RandomGenerator.cpp

        States/AntState.cpp
        States/FoodSearchState.cpp
        States/HomeSearchState.cpp
        States/RepellentPheromoneState.cpp
        States/AlertColonyState.cpp
        States/EnemySearchState.cpp
        States/AttackEnemyState.cpp
        States/DefendingState.cpp
        States/ScoutingState.cpp
        States/AtHomeState.cpp
        States/LayingState.cpp

        World/WorldData.cpp
        World/Sensor.cpp
        Ants/Ant.cpp
        World/MapGenerator.cpp
        World/PheromoneMap.cpp
        World/Map.cpp
        World/Colony.cpp
        World/World.cpp
        Renderer/Renderer.cpp
        App.cpp)

add_executable(Ants ${Sources} main.cpp)

target_include_directories(Ants PUBLIC .)

target_include_directories(Ants PUBLIC ../Geometry/GeometryEntities)

target_link_libraries(Ants sfml-graphics)