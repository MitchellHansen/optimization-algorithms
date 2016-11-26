cmake_minimum_required(VERSION 3.6)
project(Lab1)

set(SFML_COMPONENTS graphics window system network audio)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(SFML 2.1 COMPONENTS ${SFML_COMPONENTS} REQUIRED)
message(STATUS "SFML found: ${SFML_FOUND}")
include_directories(${SFML_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp mtrand.cpp mtrand.h)
add_executable(Lab1 ${SOURCE_FILES})
target_link_libraries (Lab1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})