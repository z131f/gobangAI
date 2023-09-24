cmake_minimum_required(VERSION 3.26)
project(gobang C)

set(CMAKE_C_STANDARD 11)

link_libraries(libeasyx.a)

add_executable(gobang main.c
        ai.h)
