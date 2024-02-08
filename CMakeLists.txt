cmake_minimum_required(VERSION 3.12)

project(RaycastingMiniFB)

add_subdirectory(dependencies/minifb)

#set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp screen.cpp)

#find_package(MiniFB REQUIRED)

target_link_libraries(${PROJECT_NAME} -lucrt minifb)

