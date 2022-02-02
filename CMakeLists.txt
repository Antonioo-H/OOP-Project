cmake_minimum_required(VERSION 3.20)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP_Project
        main.cpp src/Cell.cpp src/Snake.cpp src/Food.cpp src/Board.cpp src/Game.cpp src/Apple.cpp src/Poisoned_Apple.cpp src/Eroare.cpp headers/Observer.h)

target_include_directories(OOP_Project PRIVATE libraries/rlutil.h)