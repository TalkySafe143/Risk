#include "Territorio.h"

int Territorio::getId() const {
    return id;
}

void Territorio::setId(int id) {
    Territorio::id = id;
}

int Territorio::getTropas() const {
    return tropas;
}

void Territorio::setTropas(int tropas) {
    Territorio::tropas = tropas;
}

void Territorio::modificarTropas(int action) {
    if (action < 0) Territorio::tropas--;
    else Territorio::tropas++;
}
