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

void agregarTerritorio(Territorio nuevo) {
    Continente::territorios.push_back(nuevo);
}

int eliminarTerritorio(Territorio eliminar) {
    list<Territorio>::iterator it = Continente::territorios.begin();

    for (; it != Continente::territorios.end(); it++) {
        if (eliminar.getIdTerritorio() == it->getIdTerritorio()) {
            Continente::territorios.erase(it);
            return 1;
        }
    }

    return -1;
}

Territorio encontrarTerritorio(string id) {
    for (Territorio territorio: Continente::territorios) {
        if (territorio.getIdTerritorio() == id) {
            return territorio;
        }
    }
    Territorio notFound;
    notFound.setNombre("-1");

    return notFound;
}
