cmake_minimum_required(VERSION 3.12)

project(RaycastingMiniFB)

add_subdirectory(dependencies/minifb)

#set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp screen.cpp world.cpp player.cpp math.cpp camera.cpp util.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-sEXPORT_NAME='frodo_lives' -s ASYNCIFY")

if(WIN32)
  target_link_libraries(${PROJECT_NAME} -lucrt minifb)
else()
  target_link_libraries(${PROJECT_NAME} minifb)
endif()
