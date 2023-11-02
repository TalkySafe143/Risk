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
    static bool compareFieldLists(list<Territorio> a, list<Territorio> b) {
            if (a.size() != b.size()) return false;

            a.sort(); b.sort();

            list<Territorio>::iterator itA = a.begin();
            list<Territorio>::iterator itB = b.begin();

            for (; itA != a.end() && itB != b.end(); itA++, itB++) {
                if (itA->getIdTerritorio() != itB->getIdTerritorio()) return false;
            }

            return true;
    }

    /**
     * Esta funcion tiene como proposito extraer la frecuencia de los caracteres del archivo de
     * texto indicado
     * @param file Nombre del archivo de texto a analizar
     * @return Mapa con la frecuencia de los caracteres (Mapa['a'] es -1 si hay algún error)
     */
    static map<char, int> getFreq(string file);
};


#endif //PROYECTO_UTILS_H
