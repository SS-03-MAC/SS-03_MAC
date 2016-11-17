cmake_minimum_required(VERSION 3.6)
project(network)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(NETWORK_SOURCE_FILES TcpServer.cpp)

add_library(network ${NETWORK_SOURCE_FILES})
