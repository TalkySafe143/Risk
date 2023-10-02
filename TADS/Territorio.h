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

    [[nodiscard]] const string &getIdContinente() const;

    void setIdContinente(const string &idContinente);

    [[nodiscard]] int getTropas() const;

    void setTropas(int tropas);

private:
    string idTerritorio;
    string nombre;
    string idContinente;
    int tropas;
};


#endif //PROYECTO_TERRITORIO_H
