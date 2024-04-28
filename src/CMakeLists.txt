# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(echoservice)

include(GenerateProtos.cmake)

add_library(
  echolib #library name
  echo_server.cc #sources
  ) #headers
target_link_libraries(echolib protolib)
target_include_directories(echolib PUBLIC ${ECHO_INCLUDE_DIR})
add_dependencies(echolib protolib)
