# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(echoservice)

add_executable(echo-client echo-client.cc)
target_link_libraries(echo-client protolib)
add_dependencies(echo-client protolib)

set_target_properties(echo-client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
