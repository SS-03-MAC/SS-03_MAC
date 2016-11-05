cmake_minimum_required(VERSION 3.6)
project(httpParsing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(NETWORK_SOURCE_FILES httpHeader.cpp httpHeader.h httpHeaderCollection.cpp httpHeaderCollection.h httpUtils.cpp httpUtils.h httpRequestHeaderCollection.cpp httpRequestHeaderCollection.h httpResponseHeaderCollection.cpp httpResponseHeaderCollection.h AbsPath.cpp AbsPath.h)
add_library(httpParsing ${NETWORK_SOURCE_FILES})

add_executable(httpParsingTest ${NETWORK_SOURCE_FILES} main.cpp)
