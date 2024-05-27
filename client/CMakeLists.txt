# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(echoservice)

add_executable(echo_client echo_client.cc)
target_link_libraries(echo_client protolib)
add_dependencies(echo_client protolib)

set_target_properties(echo_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
