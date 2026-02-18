cmake_minimum_required(VERSION 3.10)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(runsim
    main.cpp
    MapGenerator.cpp
    Robot.cpp
    Simulator.cpp
)

add_custom_command(TARGET runsim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/graph.py
            $<TARGET_FILE_DIR:runsim>/graph.py
)

find_package(OpenMP REQUIRED)
target_link_libraries(runsim OpenMP::OpenMP_CXX)

if (MSVC)
    target_compile_options(runsim PRIVATE /W4)
else()
    target_compile_options(runsim PRIVATE -Wall -Wextra -Wpedantic)
endif()
