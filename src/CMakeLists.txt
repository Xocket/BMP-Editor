cmake_minimum_required(VERSION 3.25)
project(Building)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")

set(CMAKE_CXX_STANDARD 23)

add_executable(Building main.cpp Timer.cpp Console.cpp tinyimage.cpp Program.cpp Pixel.cpp nodeQueue.cpp Console.cpp ImageBMP.cpp nodeList.cpp nodeMesh.cpp pointerStack.cpp)
