cmake_minimum_required(VERSION 3.26)
project(Proyecto)

set(CMAKE_CXX_STANDARD 20)


add_executable(Proyecto main.cpp
        TADS/Carta.cpp
        TADS/Continente.cpp
        TADS/Grafo.cpp
        TADS/Huffman.cpp
        TADS/Interfaces.cpp
        TADS/Jugador.cpp
        TADS/nodoB.cpp
        TADS/NodoG.cpp
        TADS/Risk.cpp
        TADS/Territorio.cpp
        TADS/Utils.cpp
        TADS/Carta.h
        TADS/Continente.h
        TADS/Grafo.h
        TADS/Huffman.h
        TADS/Interfaces.h
        TADS/Jugador.h
        TADS/nodoB.h
        TADS/NodoG.h
        TADS/Risk.h
        TADS/Territorio.h
        TADS/Utils.h

)


