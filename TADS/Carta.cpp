#include "Carta.h"

const string &Carta::getId() const {
    return id;
}

void Carta::setId(const string &id) {
    Carta::id = id;
}

const string &Carta::getIdTerritorio() const {
    return idTerritorio;
}

void Carta::setIdTerritorio(const string &idTerritorio) {
    Carta::idTerritorio = idTerritorio;
}

bool Carta::isComodin() const {
    return comodin;
}

void Carta::setComodin(bool comodin) {
    Carta::comodin = comodin;
}

int Carta::getValue() const {
    return value;
}

void Carta::setValue(int value) {
    Carta::value = value;
}


