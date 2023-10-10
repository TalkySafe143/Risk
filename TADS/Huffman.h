//
// Created by talkysafe143 on 1/10/23.
//

#ifndef PROYECTO_HUFFMAN_H
#define PROYECTO_HUFFMAN_H

#include <iostream>
#include "ArbBin.h"
#include <map>

using namespace std;

struct FreqChar {
    char c;
    int freq;
};

class Huffman {
private:
    ArbBin<NodoB<FreqChar>> tree;
public:
    /**
     * Esta funcion tiene como proposito contruir el arbol de Huffman
     * @param freq La frecuencia de los caracteres del archivo de configuracion
     */
    void contruirArbol(map<char, int> freq);

    /**
     * Esta funcion tiene como proposito decodificar un archivo binario y escribir un archivo de texto
     * con la decodificacion
     * @param file El nombre del archivo binario
     * @return El nombre del archivo de texto escrito ("\0" si se produjo un error)
     * LA CLASE QUE LLAME A ESTE METODO TIENE LA RESPONSABILIDAD DE BORRAR EL ARCHIVO DE TEXTO
     */
    string decode(string file);

    /**
     * Esta funcion tiene como proposito codificar un archivo de texto y escribir un archivo binario
     * con la codificacion de dicho archivo
     * @param file El nombre del archivo de texto
     * @return El nombre del archivo binario escrito ("\0" si se produjo un error)
     * LA CLASE QUE LLAME A ESTE METODO TIENE LA RESPONSABILIDAD DE BORRAR EL ARCHIVO DE TEXTO
     */
    string encode(string file);
};


#endif //PROYECTO_HUFFMAN_H
