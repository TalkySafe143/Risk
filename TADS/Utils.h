//
// Created by talkysafe143 on 1/10/23.
//

#ifndef PROYECTO_UTILS_H
#define PROYECTO_UTILS_H
#include<iostream>
#include<list>
#include "Territorio.h"
using namespace std;

class Utils {
public:
    /**
     * Esta funcion tiene como proposito retornar si dos listas de territorios son iguales
     * @param a La primera lista de territorios
     * @param b La segunda lista de territorios
     * @return Un booleano indicando si son iguales o no
     */
    static bool compareFieldLists(list<Territorio> a, list<Territorio> b);
};


#endif //PROYECTO_UTILS_H
