cmake_minimum_required(VERSION 3.6)
project(edutls C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra  -std=c++11 -O0")

file(GLOB EDUTLS_SOURCE_FILES bignum/*.cpp crypto/*/*.cpp tls/*/*.cpp)

add_library(edutls ${EDUTLS_SOURCE_FILES})
SET_TARGET_PROPERTIES(edutls PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(edutls gmp)
