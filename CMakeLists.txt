cmake_minimum_required(VERSION 3.4.3)


set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")



file(GLOB l4_SOURCES "lab4/*.cpp" "lab4/*.c")
file(GLOB l4_HEADERS "lab4/*.h" "lab4/*.hpp")
add_executable(Lab4 ${l4_SOURCES} ${l4_HEADERS})
set_target_properties(Lab4 PROPERTIES LINKER_LANGUAGE CXX)

file(GLOB l3_SOURCES "lab3/*.cpp" "lab3/*.c")
file(GLOB l3_HEADERS "lab3/*.h" "lab3/*.hpp")
add_executable(Lab3 ${l3_SOURCES} ${l3_HEADERS})
set_target_properties(Lab3 PROPERTIES LINKER_LANGUAGE CXX)

file(GLOB l2_SOURCES "lab2/*.cpp" "lab2/*.c")
file(GLOB l2_HEADERS "lab2/*.h" "lab2/*.hpp")
add_executable(Lab2 ${l2_SOURCES} ${l2_HEADERS})
set_target_properties(Lab2 PROPERTIES LINKER_LANGUAGE CXX)

file(GLOB l1_SOURCES "lab1/*.cpp" "lab1/*.c")
file(GLOB l1_HEADERS "lab1/*.h" "lab1/*.hpp")
add_executable(Lab1 ${l1_SOURCES} ${l1_HEADERS})
set_target_properties(Lab1 PROPERTIES LINKER_LANGUAGE CXX)
