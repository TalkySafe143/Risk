cmake_minimum_required(VERSION 3.26)
project(Proyecto)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto main.cpp
        TADS/Territorio.h
        TADS/Territorio.cpp
        TADS/Tropa.cpp
        TADS/Tropa.h
        TADS/Carta.cpp
        TADS/Carta.h
        TADS/Jugador.cpp
        TADS/Jugador.h)
