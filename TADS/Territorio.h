#ifndef PROYECTO_TERRITORIO_H
#define PROYECTO_TERRITORIO_H

#include <bits/stdc++.h>

using namespace std;

class Territorio {
public:

<<<<<<< HEAD
    bool operator < (const Territorio& a) { return this->getIdTerritorio() < a.getIdTerritorio(); };

    string &getIdTerritorio() const;
=======
    bool operator == (Territorio a) { return a.getIdTerritorio()==this->getIdTerritorio(); };

    bool operator < (Territorio& a) { return this->getIdTerritorio() < a.getIdTerritorio(); };

    string getIdTerritorio();
>>>>>>> 34f2d73d36b793457887af9e65bcb0dff9b11520

    void setIdTerritorio(const string &idTerritorio);

    const string &getNombre() const;

    void setNombre(const string &nombre);

    const string &getIdContinente() const;

    void setIdContinente(const string &idContinente);

<<<<<<< HEAD
    getTropas() const;
=======
    int getTropas();
>>>>>>> 34f2d73d36b793457887af9e65bcb0dff9b11520

    void setTropas(int tropas);

private:
    string idTerritorio;
    string nombre;
    string idContinente;
    int tropas=0;
};


#endif //PROYECTO_TERRITORIO_H
