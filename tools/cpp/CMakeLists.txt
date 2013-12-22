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

ADD_EXECUTABLE(console
              ../cli_lib/console.cc
              ../cli_lib/key/key_seq.cc
              ../cli_lib/key/key_map.cc
              ../cli_lib/command/command.cc
              ../cli_lib/command/param_comple/file_behavior.cc
              ../cli_lib/command/builtin/help.cc
              ../cli_lib/command/builtin/history.cc
              ../cli_lib/command/builtin/script.cc
              ../cli_lib/command/builtin/editor.cc
              ../cli_lib/command/builtin/mode_select.cc
              ../cli_lib/command/builtin/system_func.cc
              ../cli_lib/command/builtin/shell_exe.cc
              ../cli_lib/mode/builtin/normal.cc
              sample.cc)
#ADD_EXECUTABLE(test/test_main test/main.cpp key_seq.cc key_map.cc)

set_target_properties(console PROPERTIES LINK_FLAGS "-lncurses")
set_target_properties(console PROPERTIES COMPILE_FLAGS "-Wall -ansi -pedantic -I ../cli_lib ")

set(CMAKE_CXX_FLAGS_DEBUG "-g")
