cmake_minimum_required(VERSION 3.6)
project(staticContentServer)

add_subdirectory(httpParsing)
add_subdirectory(network)
add_subdirectory(pexec)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp serverSettings.cpp serverSettings.h filesystemUtils.cpp filesystemUtils.h pexec/pexec.cpp pexec/pexec.h)
add_executable(staticContentServer ${SOURCE_FILES})
target_link_libraries(staticContentServer httpParsing network pexec)