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

    /**
    * Esta funcion tiene como proposito agregar un nuevo territorio al continente
    * @param nuevo El territorio nuevo a agregar
    */
    void agregarTerritorio(Territorio nuevo);

    /**
    * Esta funcion tiene como proposito eliminar un territorio en especifico
    * @param eliminar El territorio que se requiere eliminar
    * @return Un codigo de estado
    *       1: Todo salio bien
    *       -1: Algo salio mal
    */
    int eliminarTerritorio(Territorio eliminar);

    /**
    * Esta funcion tiene como proposito encontrar y retornar un territorio del continente
    * @param id El ID del territorio a buscar
    * @return El territorio encontrado, si no existe en el continente, el nombre del territorio va a ser "-1"
    */
    Territorio encontrarTerritorio(string id);

private:
    string id;
    string nombre;
    list<Territorio> territorios;
};


#endif //PROYECTO_CONTINENTE_H
