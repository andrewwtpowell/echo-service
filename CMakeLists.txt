# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(service-container)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(src)
add_subdirectory(external)
