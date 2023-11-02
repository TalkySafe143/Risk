#ifndef PROYECTO_TERRITORIO_H
#define PROYECTO_TERRITORIO_H

#include <bits/stdc++.h>

using namespace std;

class Territorio {
public:

    bool operator == (Territorio a) { return a.getIdTerritorio()==this->getIdTerritorio(); };

    bool operator < (Territorio& a) { return this->getIdTerritorio() < a.getIdTerritorio(); };

    string getIdTerritorio();

    void setIdTerritorio(const string &idTerritorio);

    const string &getNombre() const;

    void setNombre(const string &nombre);

    const string &getIdContinente() const;

    void setIdContinente(const string &idContinente);

    int getTropas();

    void setTropas(int tropas);

    bool ocupado;
private:
    string idTerritorio;
    string nombre;
    string idContinente;
    int tropas=0;
};


#endif //PROYECTO_TERRITORIO_H
