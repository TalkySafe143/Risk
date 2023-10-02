//
// Created by talkysafe143 on 4/09/23.
//

#include "Jugador.h"

const list<Carta> &Jugador::getCartas() const {
    return cartas;
}

void Jugador::setCartas(const list<Carta> &cartas) {
    Jugador::cartas = cartas;
}

const list<Territorio> &Jugador::getTerritorios() const {
    return territorios;
}

void Jugador::setTerritorios(const list<Territorio> &territorios) {
    Jugador::territorios = territorios;
}

const string &Jugador::getId() const {
    return id;
}

void Jugador::setId(const string &id) {
    Jugador::id = id;
}

const string &Jugador::getNombre() const {
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
