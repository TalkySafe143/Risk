//
// Created by talkysafe143 on 1/10/23.
//

#ifndef PROYECTO_HUFFMAN_H
#define PROYECTO_HUFFMAN_H

#include "ArbBin.h"
#include "nodoB.h"
#include "Risk.h"

using namespace std;

struct FreqChar {
    char c;
    int freq;
    bool operator <(FreqChar a){ return this->c < a.c; }
};

class Huffman {
private:
    ArbBin<FreqChar>* tree = new ArbBin<FreqChar>();
public:

    /**
     * Esta funcion tiene como objetivo escribir un archivo de texto para guardar el progreso del juego
     * @param game Es la partida actual que se esta jugando
     * @param file Es el nombre del archivo deseado para guardar partida
     * @return Un codigo de estado
     *      1: Si todo salió bien
     *      -1: Si alog salio mal
    */
    int guardarPartida(Risk game, string file);

    /**
     * Esta funcion tiene como proposito contruir el arbol de Huffman
     * @param freq La frecuencia de los caracteres del archivo de configuracion
     */
    void construirArbol(map<char, int> freq);

    /**
     * Esta funcion tiene como proposito hallar el codigo Huffman correspondiente 
     * al caracter seleccionado
     * @param c Caracter seleccionado 
     * @param tree arbol huffman
     * @return codigo huffman
     */
    string obtenerCodigoHuffman(char c, ArbBin<FreqChar>* tree, string curr);

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

