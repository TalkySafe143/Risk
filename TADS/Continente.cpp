//
// Created by talkysafe143 on 1/10/23.
//

#include "Continente.h"

const string &Continente::getId() const {
    return id;
}

void Continente::setId(const string &id) {
    Continente::id = id;
}

const string &Continente::getNombre() const {
    return nombre;
}

void Continente::setNombre(const string &nombre) {
    Continente::nombre = nombre;
}

const list<Territorio> &Continente::getTerritorios() const {
    return territorios;
}

void Continente::setTerritorios(const list<Territorio> &territorios) {
    Continente::territorios = territorios;
}
