cmake_minimum_required(VERSION 3.24)
project(PR1 C)

set(CMAKE_C_STANDARD 17)

add_executable(PR1 src/main.c src/test.c src/purchase.c src/movie.c src/menu.c src/cinema.c src/api.c include/menu.h)
