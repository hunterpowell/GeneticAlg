cmake_minimum_required(VERSION 3.10)
project(CRobots)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(robots
    main.cpp
    MapGenerator.cpp
    Robot.cpp
    
)
