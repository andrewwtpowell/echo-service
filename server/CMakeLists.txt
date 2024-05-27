# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(echoservice)

add_executable(echo_server echo_server.cc)
target_link_libraries(echo_server protolib)
add_dependencies(echo_server protolib)

set_target_properties(echo_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
