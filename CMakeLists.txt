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

#target_include_directories(Ants PUBLIC .)

target_include_directories(Ants PUBLIC Old)

target_include_directories(Ants PUBLIC ../Geometry/GeometryEntities)

target_link_libraries(Ants sfml-graphics)


#####################################################################################

set(AntStates
        New/creature/AI/state/State.cpp
        New/creature/AI/state/antState/WorkerAI.cpp
        New/creature/AI/state/antState/QueenAI.cpp
        New/creature/AI/state/antState/WarriorAI.cpp
        New/creature/AI/state/antState/AntState.cpp
        New/creature/AI/state/antState/FoodSearchState.cpp
        New/creature/AI/state/antState/HomeSearchState.cpp
        New/creature/AI/state/antState/RepellentState.cpp
        New/creature/AI/state/antState/EnemySearchState.cpp
        )

set(Ant
        New/creature/ant/antData/PheromoneGland.cpp
        New/creature/ant/antData/ResourceSack.cpp
        New/creature/ant/Ant.cpp
        ${AntStates}
        )

set(NewSources
        New/food/FoodSource.cpp
        New/colony/Hive.cpp
        New/colony/Colony.cpp
        New/world/foodMap/NaiveFoodMap.cpp
        New/world/hiveMap/NaiveHiveMap.cpp
        New/world/creatureMap/NaiveCreatureMap.cpp
        New/world/pheromoneMap/NaivePheromoneMap.cpp
        New/world/objectMap/NaiveObjectMap.cpp

        New/world/World.cpp)

add_executable(NewAnts New/main.cpp ${NewSources} ${Ant})

target_include_directories(NewAnts PUBLIC .)

target_include_directories(NewAnts PUBLIC New)

target_include_directories(NewAnts PUBLIC ../Geometry/GeometryEntities)