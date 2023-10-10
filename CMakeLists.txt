cmake_minimum_required(VERSION 3.26)
project(Proyecto)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto main.cpp
        TADS/Territorio.h
        TADS/Territorio.cpp
        TADS/Carta.cpp
        TADS/Carta.h
        TADS/Jugador.cpp
        TADS/Jugador.h
        TADS/ArbBin.cpp
        TADS/ArbBin.h
        TADS/nodoB.cpp
        TADS/nodoB.h
        TADS/Risk.cpp
        TADS/Risk.h
        TADS/Continente.cpp
        TADS/Continente.h
        TADS/Utils.cpp
        TADS/Utils.h
        TADS/Interfaces.cpp
        TADS/Interfaces.h
        TADS/Huffman.cpp
        TADS/Huffman.h
        TADS/ArbBin.cpp
)
