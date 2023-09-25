#include "Carta.h"

const string &Carta::getId() const {
    return id;
}

void Carta::setId(const string &id) {
    Carta::id = id;
}

const string &Carta::getTipoUnidad() const {
    return tipoUnidad;
}

void Carta::setTipoUnidad(const string &tipoUnidad) {
    Carta::tipoUnidad = tipoUnidad;
}

const string &Carta::getIdTerritorio() const {
    return idTerritorio;
}

void Carta::setIdTerritorio(const string &idTerritorio) {
    Carta::idTerritorio = idTerritorio;
}
