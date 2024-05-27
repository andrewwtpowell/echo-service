# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(echoservice)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(proto)
