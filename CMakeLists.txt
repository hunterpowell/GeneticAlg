cmake_minimum_required(VERSION 3.10)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: optimization flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

add_executable(runsim
    main.cpp
    MapGenerator.cpp
    Robot.cpp
    Simulator.cpp
)
