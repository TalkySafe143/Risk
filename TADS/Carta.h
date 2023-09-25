#ifndef PROYECTO_CARTA_H
#define PROYECTO_CARTA_H
#include <iostream>

using namespace std;

class Carta {

private:
    string id;
    string tipoUnidad;
    string idTerritorio; 

public:
    [[nodiscard]] const string &getId() const;

    void setId(const string &id);

    [[nodiscard]] const string &getTipoUnidad() const;

    void setTipoUnidad(const string &tipoUnidad);

    [[nodiscard]] const string &getIdTerritorio() const;

    void setIdTerritorio(const string &idTerritorio);

};


#endif //PROYECTO_CARTA_H
