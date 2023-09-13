#include "Tropa.h"

const string &Tropa::getTipo() const {
    return tipo;
}

void Tropa::setTipo(const string &tipo) {
    Tropa::tipo = tipo;
}
