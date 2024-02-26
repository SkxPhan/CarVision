cmake_minimum_required(VERSION 3.5.0)
project(CarVision VERSION 0.1.0 LANGUAGES C CXX)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(CarVision src/main.cpp)

# Link the executable with OpenCV libraries
target_link_libraries(CarVision ${OpenCV_LIBS})