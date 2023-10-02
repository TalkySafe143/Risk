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
    [[nodiscard]] const string &getId() const;

    void setId(const string &id);

    [[nodiscard]] const string &getIdTerritorio() const;

    void setIdTerritorio(const string &idTerritorio);

    [[nodiscard]] bool isComodin() const;

    void setComodin(bool comodin);

    [[nodiscard]] int getValue() const;

    void setValue(int value);

};


#endif //PROYECTO_CARTA_H
