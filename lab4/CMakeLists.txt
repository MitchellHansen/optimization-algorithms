cmake_minimum_required(VERSION 3.4.3)

add_project(Lab4)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h" "*.hpp")

set(SOURCE_FILES ${HEADERS} ${SOURCES} )

add_executable(Lab4 ${SOURCE_FILES})
