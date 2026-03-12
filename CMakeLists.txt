cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(demo LANGUAGES CXX)

file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable(demo ${SOURCES})
target_include_directories(demo PRIVATE .)

find_package(Threads REQUIRED)
target_link_libraries(demo PUBLIC Threads::Threads)