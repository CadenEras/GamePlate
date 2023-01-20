cmake_minimum_required(VERSION 3.24)
project(c_pas_cool_gameplate C)

set(CMAKE_C_STANDARD 17)

add_executable(c_pas_cool_gameplate main.c headers/Checker/bases.h headers/Checker/interface.h headers/Checker/checkerGame.h sources/Checker/checkerGame.c sources/Checker/interface.c)
