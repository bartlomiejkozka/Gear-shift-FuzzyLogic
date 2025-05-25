cmake_minimum_required(VERSION 3.14)

project(GearShift-FuzzyLogic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(GearShift src/GearShift.cpp)
target_include_directories(GearShift PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(GearShift-Fuzzy src/main.cpp)
target_link_libraries(GearShift-Fuzzy PRIVATE GearShift)

# CLI11 tool

include(FetchContent)
FetchContent_Declare(
    cli11_proj
    QUIET
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.3.2
)

FetchContent_MakeAvailable(cli11_proj)

target_link_libraries(GearShift-Fuzzy PRIVATE CLI11::CLI11)
