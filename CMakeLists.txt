cmake_minimum_required(VERSION 3.10)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
configure_file(graph.py ${CMAKE_BINARY_DIR}/Debug/graph.py COPYONLY)

# Optional: optimization flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

add_executable(runsim
    main.cpp
    MapGenerator.cpp
    Robot.cpp
    Simulator.cpp
)
