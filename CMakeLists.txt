cmake_minimum_required(VERSION 2.8.12)

cmake_policy(SET CMP0048 NEW)

project(Project)

#------------------ Google Test library ------------------------------------

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

#---------------------------------------------------------------------------

#Add flags for compiling
set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -pedantic")

#Add all the sources of the model into SOURCES
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

#Removing main out of the model in SOURCES
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

#Add all the test files into TEST
file(GLOB TEST ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

#Make a library from the model
add_library(Project_model ${SOURCES})

add_executable(Project ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp src/DistributionChain.cpp src/DistributionChain.h)

#Link the model to the project
target_link_libraries(Project Project_model)

add_executable(Test ${TEST})

#Link model to the test cases
target_link_libraries(Test Project_model gtest_main)
