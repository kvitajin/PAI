cmake_minimum_required(VERSION 3.17)
project(cv1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_STANDARD 20)

add_executable(cv1 main.cpp)