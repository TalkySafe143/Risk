#ifndef PROYECTO_TERRITORIO_H
#define PROYECTO_TERRITORIO_H

#include <bits/stdc++.h>

using namespace std;

class Territorio {
private:
    int id;
    int tropas;
public:
    int getId() const;

    void setId(int id);

    int getTropas() const;

    void setTropas(int tropas);

    void modificarTropas(int action);

};


#endif //PROYECTO_TERRITORIO_H
