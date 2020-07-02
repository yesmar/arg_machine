# Arg Machine © 2017, 2020 Ramsey Dow.
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(arg_machine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

if(UNIX)
  set(CMAKE_C_FLAGS "${CMAKE_CPP_FLAGS} -Wall -Wextra -Werror")
elseif(WIN32)
  set(CMAKE_C_FLAGS "${CMAKE_CPP_FLAGS} /W4 /WX")
endif()

add_executable(arg_machine
  ${CMAKE_SOURCE_DIR}/sample.cc
)

target_include_directories(arg_machine
  PRIVATE ${CMAKE_SOURCE_DIR}
)
