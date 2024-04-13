cmake_minimum_required(VERSION 3.20.0)
project(CarVision VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

add_executable(CarVision src/main.cpp)
target_link_libraries(CarVision PRIVATE ${OpenCV_LIBS})
