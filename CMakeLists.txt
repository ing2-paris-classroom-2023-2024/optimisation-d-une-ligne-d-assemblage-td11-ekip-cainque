cmake_minimum_required(VERSION 3.23)
project(Ligne_assemblage C)

set(CMAKE_C_STANDARD 11)

add_executable(Ligne_assemblage Graphe.h exclusions.h main.c precedences.h cycle_temp.h)
