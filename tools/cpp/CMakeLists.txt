cmake_minimum_required(VERSION 2.6)

PROJECT(iunit-cli)

IF(UNIX)
    include_directories(/usr/include ./)
    link_directories(/usr/lib)
ENDIF(UNIX)
IF(APPLE)
    include_directories(/opt/local/include /usr/include ./)
    link_directories(/opt/local/lib /usr/lib)
ENDIF(APPLE)

ADD_EXECUTABLE(console sample.cc ../cli_lib/key_seq.cc ../cli_lib/key_map.cc)
#ADD_EXECUTABLE(test/test_main test/main.cpp key_seq.cc key_map.cc)

set_target_properties(console PROPERTIES LINK_FLAGS -lncurses)
set_target_properties(console PROPERTIES COMPILE_FLAGS "-Wall -ansi -pedantic -I ../cli_lib")

set(CMAKE_CXX_FLAGS_DEBUG "-g")
