cmake_minimum_required(VERSION 3.26)
project(TA_PO)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TA_PO
        DFA.cpp
        DFA.h
        json.hpp
        main.cpp)
