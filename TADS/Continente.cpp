//
// Created by talkysafe143 on 1/10/23.
//

#include "Continente.h"

string Continente::getId() {
    return id;
}

void Continente::setId(const string &id) {
    Continente::id = id;
}

string Continente::getNombre() {
    return nombre;
}

void Continente::setNombre(const string &nombre) {
    Continente::nombre = nombre;
}

list<Territorio> &Continente::getTerritorios() {
    return territorios;
}

void Continente::setTerritorios(const list<Territorio> &territorios) {
    Continente::territorios = territorios;
}

void Continente::agregarTerritorio(Territorio nuevo) {
    Continente::territorios.push_back(nuevo);
}

int Continente::eliminarTerritorio(Territorio eliminar) {
    list<Territorio>::iterator it = Continente::territorios.begin();

    for (; it != Continente::territorios.end(); it++) {
        if (eliminar.getIdTerritorio() == it->getIdTerritorio()) {
            Continente::territorios.erase(it);
            return 1;
        }
    }

    return -1;
}

Territorio &Continente::encontrarTerritorio(string id) {
    for (Territorio &territorio: Continente::territorios) {
        if (territorio.getIdTerritorio() == id) {
            return territorio;
        }
    }
    notFound.setNombre("-1");

    return notFound;
}
