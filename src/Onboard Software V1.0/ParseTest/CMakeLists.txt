# cmake_minimum_required(VERSION <specify CMake version here>)
project(ParseTest)

set(CMAKE_CXX_STANDARD 14)

add_executable(ParseTest main.cpp Message.cpp Message.h BitHandler.h Data.h)