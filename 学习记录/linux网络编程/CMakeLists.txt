cmake_minimum_required(VERSION 3.10)

project(SocketExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server PRIVATE pthread)
target_link_libraries(client PRIVATE pthread)