#include "Carta.h"

int Carta::getIdTerritorio() const {
    return idTerritorio;
}

void Carta::setIdTerritorio(int idTerritorio) {
    Carta::idTerritorio = idTerritorio;
}

const string &Carta::getTipoTropa() const {
    return tipoTropa;
}

void Carta::setTipoTropa(const string &tipoTropa) {
    Carta::tipoTropa = tipoTropa;
}

bool Carta::isComodin() const {
    return comodin;
}

void Carta::setComodin(bool comodin) {
    Carta::comodin = comodin;
}
