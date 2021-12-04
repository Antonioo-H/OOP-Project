cmake_minimum_required(VERSION 3.20)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP_Project
        main.cpp src/Cell.cpp headers/Cell.h src/Snake.cpp headers/Snake.h src/Food.cpp headers/Food.h src/Board.cpp headers/Board.h src/Game.cpp headers/Game.h)
