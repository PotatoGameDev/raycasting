cmake_minimum_required(VERSION 3.12)

project(RaycastingMiniFB)

add_subdirectory(dependencies/minifb)

#set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp screen.cpp world.cpp player.cpp)

#find_package(MiniFB REQUIRED)

if(WIN32)
  target_link_libraries(${PROJECT_NAME} -lucrt minifb)
else()
  target_link_libraries(${PROJECT_NAME} minifb)
endif()
