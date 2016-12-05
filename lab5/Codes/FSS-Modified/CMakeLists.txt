cmake_minimum_required(VERSION 3.6)
project(FSS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    bin/FSS
    FSS.cpp
    FSS.h
    FSSB.cpp
    FSSB.h
    FSSNW.cpp
    FSSNW.h
    fss.txt
    main.cpp
    makefile)

add_executable(FSS ${SOURCE_FILES})