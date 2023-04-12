cmake_minimum_required(VERSION 3.23)
project(projet_RN40_final C)

set(CMAKE_C_STANDARD 99)

add_executable(projet_RN40_final main.c structures.h Individu/individu.h Individu/individu.c Population/population.c Population/population.h)
