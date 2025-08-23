cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 11)
project(sandSimulation VERSION 1.0)
set(sandSimulation VERSION 1.0)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

file(COPY "assets" DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB_RECURSE SAND_SIMULATION_SOURCES "src/*.cpp" "src/*.hpp")

add_executable(sandSimulation ${SAND_SIMULATION_SOURCES})

target_link_libraries(sandSimulation PRIVATE SFML::Graphics)