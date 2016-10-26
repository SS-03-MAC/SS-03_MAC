cmake_minimum_required(VERSION 3.6)
project(staticContentServer)

add_subdirectory(httpParsing)
add_subdirectory(network)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES main.cpp)
add_executable(staticContentServer ${SOURCE_FILES})
target_link_libraries(staticContentServer httpParsing network)