cmake_minimum_required(VERSION 3.10)

project(GearShift-FuzzyLogic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(GearShift src/GearShift.cpp)
target_include_directories(GearShift PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(GearShift-Fuzzy src/main.cpp)
target_link_libraries(GearShift-Fuzzy PRIVATE GearShift)
