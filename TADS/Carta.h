#ifndef PROYECTO_CARTA_H
#define PROYECTO_CARTA_H
#include <iostream>

using namespace std;

class Carta {
public:
    int getIdTerritorio() const;

    void setIdTerritorio(int idTerritorio);

    [[nodiscard]] const string &getTipoTropa() const;

    void setTipoTropa(const string &tipoTropa);

    bool isComodin() const;

    void setComodin(bool comodin);

private:
    int idTerritorio;
    string tipoTropa;
    bool comodin;
};


#endif //PROYECTO_CARTA_H
