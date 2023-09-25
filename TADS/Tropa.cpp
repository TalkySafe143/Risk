#include "Tropa.h"

const string &Tropa::getTipo() const {
    return tipo;
}

void Tropa::setTipo(const string &tipo) {
    Tropa::tipo = tipo;
}

const string &Tropa::getIdTerritorio() const {
    return idTerritorio;
}

void Tropa::setIdTerritorio(const string &idTerritorio) {
    Tropa::idTerritorio = idTerritorio;
}
