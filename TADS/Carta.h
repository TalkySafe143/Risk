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
<<<<<<< HEAD
    string &getId() const;
=======
    string getId();
>>>>>>> 34f2d73d36b793457887af9e65bcb0dff9b11520

    void setId(const string id);

<<<<<<< HEAD
    string &getIdTerritorio() const;
=======
    string getIdTerritorio();
>>>>>>> 34f2d73d36b793457887af9e65bcb0dff9b11520

    void setIdTerritorio(const string idTerritorio);

    bool isComodin() const;

    void setComodin(bool comodin);

    int getValue() const;

    void setValue(int value);

};


#endif //PROYECTO_CARTA_H
