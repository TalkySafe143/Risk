//
// Created by talkysafe143 on 1/10/23.
//

#ifndef PROYECTO_INTERFACES_H
#define PROYECTO_INTERFACES_H

#include<iostream>
#include "Risk.h"

/**
 * El proposito general de esta clase es poder desarrollar las interfaces
 * O los pasos en los que hay que imprimir o interactuar con el usuario
 * Esta clase llamara a los metodos definidos en los otros TADS y será
 * el encargado de preparar los datos para mandarlos a los TADS
 */
class Interfaces {
private:
    Risk game;
public:
    /**
     * Esta funcion tiene como proposito pedir los jugadores y asignarles las tropas a los territorios
     */
    void inicializarJuego();

    /**
     * Esta funcion tiene como proposito pedir en que territorio quiere asignar las tropas
     * @param tropas El numero de tropas a ubicar
     * @param jugador Jugador el cual quiere ubicar las tropas
     */
    void asignarTropasTerritorio(int tropas, Jugador &jugador);

    [[nodiscard]] const Risk &getGame() const;

    void setGame(const Risk &game);
};


#endif //PROYECTO_INTERFACES_H
