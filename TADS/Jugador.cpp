//
// Created by talkysafe143 on 4/09/23.
//

#include "Jugador.h"

list<Carta> Jugador::getCartas() {
    return cartas;
}

void Jugador::setCartas(const list<Carta> &cartas) {
    Jugador::cartas = cartas;
}

list<Territorio> Jugador::getTerritorios() {
    return territorios;
}

void Jugador::setTerritorios(const list<Territorio> &territorios) {
    Jugador::territorios = territorios;
}

string Jugador::getId() {
    return id;
}

void Jugador::setId(const string &id) {
    Jugador::id = id;
}

string Jugador::getNombre() {
    return nombre;
}

void Jugador::setNombre(const string &nombre) {
    Jugador::nombre = nombre;
}

const string &Jugador::getColor() const {
    return color;
}

void Jugador::setColor(const string &color) {
    Jugador::color = color;
}

list<Continente> Jugador::verificarContinentes(list<Continente> base) {
    list<Continente> occuped;

    for (Continente continente: base) {
        if (Utils::compareFieldLists(Jugador::getTerritorios(), continente.getTerritorios())) {
            occuped.push_back(continente);
        }
    }

    return occuped;
}


int Jugador::modificarTropasTerritorio(Territorio field, int num) {
    for (Territorio territorio: Jugador::getTerritorios()) {
        if (territorio.getIdTerritorio() == field.getIdTerritorio()) {
            territorio.setTropas(territorio.getTropas() + num);
            return 1;
        }
    }

    return -1;
}


void Jugador::agregarTerritorio(Territorio nuevo) {
    Jugador::territorios.push_back(nuevo);
}
