cmake_minimum_required(VERSION 3.6)
project(pexec)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(PEXEC_SOURCE_FILES pexec.cpp)

add_library(pexec ${PEXEC_SOURCE_FILES})
