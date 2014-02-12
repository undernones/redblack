cmake_minimum_required(VERSION 2.8)
project(fluids)

if (DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the build type. Options are: Debug, Release")
else()
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type. Options are: Debug, Release")
endif()

include_directories(
    .
    lib
    /opt/local/include
    /usr/local/include
)
link_directories(
    /opt/local/lib
    /usr/local/lib
)

set(CMAKE_CXX_FLAGS "-Qunused-arguments -std=c++11 -stdlib=libc++ -Wall -Wno-long-long -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g")

if (CMAKE_BUILD_TYPE MATCHES "Release")
    add_definitions(-DNDEBUG)
endif()

set(SRC Tree.cpp)
add_executable(headless main.cpp ${SRC})

message(STATUS)
message(STATUS "--------------------------------------------------------------------------------")
message(STATUS "Change a value with: cmake . -D<Variable>=<Value>")
message(STATUS "Example: cmake . -DCMAKE_BUILD_TYPE=Debug")
message(STATUS "--------------------------------------------------------------------------------")
message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    message(STATUS "Debug compiler flags: ${CMAKE_CXX_FLAGS_DEBUG}")
else()
    message(STATUS "Release compiler flags: ${CMAKE_CXX_FLAGS_RELEASE}")
endif()
message(STATUS "--------------------------------------------------------------------------------")
message(STATUS)
