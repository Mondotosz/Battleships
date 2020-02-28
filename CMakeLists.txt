cmake_minimum_required(VERSION 3.15)
project(BATTLESHIPS C)

set(CMAKE_C_STANDARD 99)

add_executable(Battleships battleships.c menu.h libraries/quit.h libraries/authentication.h libraries/help.h libraries/utilities/utilities.h libraries/scoreboard.h)