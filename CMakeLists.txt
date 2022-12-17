cmake_minimum_required(VERSION 3.24)
project(c_pas_cool_gameplate C)

set(CMAKE_C_STANDARD 17)

add_executable(c_pas_cool_gameplate main.c headers/renderer.h headers/math.h headers/Entity.h headers/Checker/Constructor.h headers/Checker/Highlighter.h headers/Checker/Checker.h headers/Checker/Checker.h sources/Checker/Checker.c sources/Checker/Constructor.c sources/Checker/Highlidhter.c)
