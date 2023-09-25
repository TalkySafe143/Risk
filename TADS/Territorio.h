#ifndef PROYECTO_TERRITORIO_H
#define PROYECTO_TERRITORIO_H

#include <bits/stdc++.h>

using namespace std;

class Territorio {
public:
    [[nodiscard]] const string &getIdTerritorio() const;

    void setIdTerritorio(const string &idTerritorio);

    [[nodiscard]] const string &getNombre() const;

    void setNombre(const string &nombre);

private:
    string idTerritorio;
    string nombre;
public:


};


#endif //PROYECTO_TERRITORIO_H
