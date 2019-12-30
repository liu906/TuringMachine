cmake_minimum_required(VERSION 3.14)
project(turing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
add_executable(Turing turing.cpp parser.cpp simulator.cpp parser.h TM.cpp TM.h simulator.h)