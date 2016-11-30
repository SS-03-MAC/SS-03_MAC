cmake_minimum_required(VERSION 3.6)
project(staticContentServer)

find_package(Yaml-Cpp REQUIRED)

add_subdirectory(httpParsing)
add_subdirectory(network)
add_subdirectory(pexec)
add_subdirectory(EduTLS/src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp server/settings.cpp server/settings.h utils/filesystem.cpp utils/filesystem.h pexec/pexec.cpp
        pexec/pexec.h server/server.cpp server/server.h)
add_executable(staticContentServer ${SOURCE_FILES})
target_link_libraries(staticContentServer httpParsing network pexec edutls gmp YAMLCPP_LIBRARY)