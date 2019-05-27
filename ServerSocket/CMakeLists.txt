cmake_minimum_required(VERSION 3.2)
project("ServerSocket")

include_directories(${CMAKE_SOURCE_DIR})

add_library(ServerSocket "ServerSocket.cpp")

add_executable(ServerDemo "${CMAKE_SOURCE_DIR}/ServerDemo.cpp")
target_link_libraries(ServerDemo ServerSocket)