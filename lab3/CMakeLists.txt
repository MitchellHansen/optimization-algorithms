cmake_minimum_required(VERSION 3.5.1)

project(Lab3)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h" "*.hpp")

set(SOURCE_FILES ${HEADERS} ${SOURCES} )

add_executable(Lab3 ${SOURCE_FILES})
