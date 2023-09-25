#ifndef PROYECTO_TROPA_H
#define PROYECTO_TROPA_H

#include <iostream>

using namespace std;

class Tropa {
public:
    [[nodiscard]] const string &getTipo() const;

    void setTipo(const string &tipo);

    [[nodiscard]] const string &getIdTerritorio() const;

    void setIdTerritorio(const string &idTerritorio);

private:
    string tipo;
    string idTerritorio;

};


#endif //PROYECTO_TROPA_H
