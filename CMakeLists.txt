cmake_minimum_required(VERSION 3.2)
project("ClientSocket")

include_directories(${CMAKE_SOURCE_DIR})

add_library(ClientSocket "ClientSocket.cpp")

add_executable(ClientDemo "${CMAKE_SOURCE_DIR}/ClientDemo.cpp")
target_link_libraries(ClientDemo ClientSocket)