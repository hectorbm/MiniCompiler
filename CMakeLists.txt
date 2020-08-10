cmake_minimum_required(VERSION 3.16)
project(MiniCompiler C)

set(CMAKE_C_STANDARD 11)

add_executable(MiniCompiler "Virtual_Machine/machine_sim.c" "Virtual_Machine/machine_sim.h")