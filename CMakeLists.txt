cmake_minimum_required(VERSION 3.21)
project(Ants)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Werror")

set(CMAKE_CXX_STANDARD 20)

set(Sources
        Old/Utils/RandomGenerator.cpp

        Old/States/AntState.cpp
        Old/States/FoodSearchState.cpp
        Old/States/HomeSearchState.cpp
        Old/States/RepellentPheromoneState.cpp
        Old/States/AlertColonyState.cpp
        Old/States/EnemySearchState.cpp
        Old/States/AttackEnemyState.cpp
        Old/States/DefendingState.cpp
        Old/States/ScoutingState.cpp
        Old/States/AtHomeState.cpp
        Old/States/LayingState.cpp

        Old/World/WorldData.cpp
        Old/World/Sensor.cpp
        Old/Ants/Ant.cpp
        Old/World/MapGenerator.cpp
        Old/World/PheromoneMap.cpp
        Old/World/Map.cpp
        Old/World/Colony.cpp
        Old/World/World.cpp
        Old/Renderer/Renderer.cpp
        App.cpp)

add_executable(Ants ${Sources} main.cpp)

target_include_directories(Ants PUBLIC .)

target_include_directories(Ants PUBLIC Old)

target_include_directories(Ants PUBLIC ../Geometry/GeometryEntities)

target_link_libraries(Ants sfml-graphics)




set(NewSources
        New/food/FoodSource.cpp
        New/hive/Hive.cpp
        New/world/foodMap/NaiveFoodMap.cpp
        New/world/hiveMap/NaiveHiveMap.cpp
        New/world/World.cpp)

add_executable(NewAnts ${NewSources} New/main.cpp)

target_include_directories(NewAnts PUBLIC .)

target_include_directories(NewAnts PUBLIC New)

target_include_directories(NewAnts PUBLIC ../Geometry/GeometryEntities)