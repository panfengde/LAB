cmake_minimum_required(VERSION 3.15)
project(LAB)

set(CMAKE_CXX_STANDARD 11)

include_directories(./includes)
include_directories(./src)

#[[include_directories(/Users/panfeng/Desktop/CMakeTest/include)
include_directories(/Users/panfeng/Desktop/CMakeTest/src)

add_library(myLib SHARED ./src/library.h ./src/library.cpp)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)#设置动态库输出目录]]


add_executable(LAB
        main.cpp
        )
