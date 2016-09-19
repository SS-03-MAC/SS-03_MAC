cmake_minimum_required(VERSION 3.6)
project(jmay)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES Execute/executer.cpp)

add_executable(executer ${SOURCE_FILES})
add_executable(executee Execute/executee.cpp)
add_executable(fork Execute/fork.cpp)