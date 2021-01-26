cmake_minimum_required(VERSION 3.17)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 14)

add_executable(SpaceInvaders main.cpp logic.h)
target_link_libraries(SpaceInvaders -lglut -lglfw -lGLEW -lGL -lGLU)