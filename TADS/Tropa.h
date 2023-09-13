#ifndef PROYECTO_TROPA_H
#define PROYECTO_TROPA_H

#include <iostream>

using namespace std;

class Tropa {
public:
    const string &getTipo() const;

    void setTipo(const string &tipo);

private:
    string tipo;
public:

};


#endif //PROYECTO_TROPA_H
