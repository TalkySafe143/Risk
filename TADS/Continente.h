//
// Created by talkysafe143 on 1/10/23.
//

#ifndef PROYECTO_CONTINENTE_H
#define PROYECTO_CONTINENTE_H

#include <iostream>
#include "Territorio.h"
using namespace std;

class Continente {
public:
    [[nodiscard]] const string &getId() const;

    void setId(const string &id);

    [[nodiscard]] const string &getNombre() const;

    void setNombre(const string &nombre);

    [[nodiscard]] const list<Territorio> &getTerritorios() const;

    void setTerritorios(const list<Territorio> &territorios);

private:
    string id;
    string nombre;
    list<Territorio> territorios;
};


#endif //PROYECTO_CONTINENTE_H
