cmake_minimum_required(VERSION 2.6)

PROJECT(iunit)

IF(UNIX)
    include_directories(/usr/include ./)
    link_directories(/usr/lib)
ENDIF(UNIX)
IF(APPLE)
    include_directories(/opt/local/include /usr/include ./)
    link_directories(/opt/local/lib /usr/lib)
ENDIF(APPLE)

ADD_EXECUTABLE(iunitdemo samples/cpp/main.cpp)

set_target_properties(iunitdemo PROPERTIES COMPILE_FLAGS "-Wall -I ./cpp")

set(CMAKE_CXX_FLAGS_DEBUG "-g")

