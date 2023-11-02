#ifndef PROYECTO_CARTA_H
#define PROYECTO_CARTA_H
#include <iostream>

using namespace std;

class Carta {

private:
    string id;
    int value;
    string idTerritorio;
    bool comodin;

public:
    string &getId();

    void setId(const string id);

    string &getIdTerritorio();

    void setIdTerritorio(const string idTerritorio);

    bool isComodin() const;

    void setComodin(bool comodin);

    int getValue() const;

    void setValue(int value);

};


#endif //PROYECTO_CARTA_H
