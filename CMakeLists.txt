cmake_minimum_required(VERSION 3.21.1)
project(NAI_SEM5)

set(CMAKE_CXX_STANDARD 14)

add_executable(NAI_SEM5
        lab1/main.cpp)

add_executable(lab2 lab2/lab2.cpp lab5/lab5.cpp)

add_executable(lab3 lab3/lab3.cpp)

add_executable(lab4 lab4/lab4.cpp)

add_executable(lab5 lab5/lab5.cpp)