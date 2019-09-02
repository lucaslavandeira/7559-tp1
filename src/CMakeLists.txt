cmake_minimum_required(VERSION 2.8.12)
project (Project)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -pedantic")

file(GLOB SOURCES "*.cpp")

add_executable(Project ${SOURCES} )

install(TARGETS Project DESTINATION bin)
