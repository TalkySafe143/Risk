#ifndef PROYECTO_TERRITORIO_H
#define PROYECTO_TERRITORIO_H

#include <bits/stdc++.h>

using namespace std;

class Territorio {
public:

    bool operator < (const Territorio& a) { return this->getIdTerritorio() < a.getIdTerritorio(); };

    string &getIdTerritorio() const;

    void setIdTerritorio(const string &idTerritorio);

    const string &getNombre() const;

    void setNombre(const string &nombre);

    const string &getIdContinente() const;

    void setIdContinente(const string &idContinente);

    getTropas() const;

    void setTropas(int tropas);

private:
    string idTerritorio;
    string nombre;
    string idContinente;
    int tropas;
};


#endif //PROYECTO_TERRITORIO_H
