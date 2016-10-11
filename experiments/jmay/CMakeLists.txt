cmake_minimum_required(VERSION 3.6)
project(jmay)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package(Yaml-Cpp REQUIRED)

set(SOURCE_FILES Execute/executer.cpp)
set(PEXEC_TEST_SRC pexec.cpp tests/pexec.cpp)

add_executable(executer ${SOURCE_FILES})
add_executable(executee Execute/executee.cpp)
add_executable(fork Execute/fork.cpp)
add_executable(pexec pexec.cpp)
add_executable(pexec_test ${PEXEC_TEST_SRC})
add_executable(client TCP/client.cpp)
add_executable(server TCP/server.cpp)
add_executable(basicServer basicServer.cpp pexec.cpp TcpServer.cpp)
add_executable(yaml yaml-test/yaml.cpp)

#link_directories(/usr/local/lib)
#add_dependencies(yaml yaml-cpp)
target_link_libraries(yaml /usr/local/lib/libyaml-cpp.a)
