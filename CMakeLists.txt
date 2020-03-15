cmake_minimum_required(VERSION 3.15)
project(BATTLESHIPS C)

set(CMAKE_C_STANDARD 99)

add_executable(Battleships battleships.c sources/help.c sources/help.h sources/authentication.c sources/authentication.h sources/utilities/utilities.c sources/utilities/utilities.h sources/game.c sources/game.h sources/score.c sources/score.h sources/utilities/logs.c sources/utilities/logs.h)