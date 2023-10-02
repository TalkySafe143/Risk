#include "Territorio.h"

const string &Territorio::getIdTerritorio() const {
    return idTerritorio;
}

void Territorio::setIdTerritorio(const string &idTerritorio) {
    Territorio::idTerritorio = idTerritorio;
}

const string &Territorio::getNombre() const {
    return nombre;
}

void Territorio::setNombre(const string &nombre) {
    Territorio::nombre = nombre;
}

const string &Territorio::getIdContinente() const {
    return idContinente;
}

void Territorio::setIdContinente(const string &idContinente) {
    Territorio::idContinente = idContinente;
}

int Territorio::getTropas() const {
    return tropas;
}

void Territorio::setTropas(int tropas) {
    Territorio::tropas = tropas;
}
