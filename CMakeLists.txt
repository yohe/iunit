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

make_directory(bin/cpp)
ADD_EXECUTABLE(bin/cpp/iunitdemo_cpp samples/cpp/main.cpp)

set_target_properties(bin/cpp/iunitdemo_cpp PROPERTIES COMPILE_FLAGS "-Wall -I ./cpp")

set(CMAKE_CXX_FLAGS_DEBUG "-g")

