# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(echoservice)

add_executable(echo-server echo-server.cc)
target_link_libraries(echo-server protolib)
add_dependencies(echo-server protolib)

set_target_properties(echo-server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
