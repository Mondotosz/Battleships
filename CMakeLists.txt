cmake_minimum_required(VERSION 3.15)
project(BATTLESHIPS C)

set(CMAKE_C_STANDARD 99)

add_executable(Battleships battleships.c libraries/help.c libraries/help.h)