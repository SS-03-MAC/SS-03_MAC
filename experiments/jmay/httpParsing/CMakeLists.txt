cmake_minimum_required(VERSION 3.6)
project(httpParsing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp httpHeader.cpp httpHeader.h httpHeaderCollection.cpp httpHeaderCollection.h httpUtils.cpp httpUtils.h)
add_executable(httpParsing ${SOURCE_FILES})