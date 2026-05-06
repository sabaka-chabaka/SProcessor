cmake_minimum_required(VERSION 3.28)
project(SProcessor)

set(CMAKE_CXX_STANDARD 20)

add_executable(SProcessor main.cpp
        transistor.cpp
        transistor.h
        gate.cpp
        gate.h
        alu.cpp
        alu.h)
