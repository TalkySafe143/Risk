//
// Created by talkysafe143 on 1/10/23.
//

#include "Huffman.h"
#include "Risk.h"
#include "Jugador.h"
#include <iostream>
#include <fstream>


/**
 * Ahí agregué la funcion en el .h, pero toca que tenga cuidado cuando escriba las cartas
 * Acuerdese que las cartas es por cada jugador en la partida, no de todo el juego
 * Toca que verifique si se esta escribiendo bien el archivo
 * 
 * Toca que le meta turbo a implementar eso porque esta parte de manejo de bits es un visag
 * Busque si algo #pragma push(1) y pille lo que hace, las estructuras y eso porque eso es un camello
 * Le recomiendo implementar esto a mas tardar el fincho ñero, porque toca comenzar a probar y 
 * mirar errores, si todo funciona bien y corregir, le recomiendo):
*/
int guardarPartida(Risk game, string file) {

    std::ofstream archivo(file);

    if (!archivo.is_open()) {
        std::cout << "La partida no ha sido guardada correctamente." << std::endl;
        return -1;
    }

    // if () {
    //     std::cout << " Esta partida no ha sido inicializada correctamente." << std::endl;
    //     return;
    // }

    const std::list<Jugador> jugadores = game.getJugadores();
    const std::list<Continente>& continentes = game.getContinentes();
    const std::list<Carta>& cartas = game.getCartas();
    const std::list<Jugador>::iterator& turno = game.getTurno();

    archivo << jugadores.size() << std::endl;
    for (auto jugador : jugadores) {
        archivo << jugador.getId() << ";" << jugador.getNombre() << ";" << jugador.getColor() << ";";

        const std::list<Territorio> territorios = jugador.getTerritorios();
        archivo << territorios.size() << ";";
        for (auto territorio : territorios) {
            archivo << territorio.getIdTerritorio() << ";" << territorio.getTropas() << ";";
        }

        const std::list<Carta>& cartasJugador = jugador.getCartas();
        archivo << cartasJugador.size() << ";";
        for (auto carta : cartasJugador) {
            archivo << carta.getId() << ";";
        }

        archivo << std::endl;
    }

    archivo.close();
    cout << "La partida ha sido guardada correctamente." << endl;

    return 1;
}

/**
 * Esta funcion tiene como proposito contruir el arbol de Huffman
 * @param freq La frecuencia de los caracteres del archivo de configuracion
 */
void Huffman::contruirArbol(map<char, int> freq){

}

/**
 * Esta funcion tiene como proposito decodificar un archivo binario y escribir un archivo de texto
 * con la decodificacion
 * @param file El nombre del archivo binario
 * @return El nombre del archivo de texto escrito ("\0" si se produjo un error)
 * LA CLASE QUE LLAME A ESTE METODO TIENE LA RESPONSABILIDAD DE BORRAR EL ARCHIVO DE TEXTO
 */
string Huffman::decode(string file){

}

/**
 * Esta funcion tiene como proposito codificar un archivo de texto y escribir un archivo binario
 * con la codificacion de dicho archivo
 * @param file El nombre del archivo de texto
 * @return El nombre del archivo binario escrito ("\0" si se produjo un error)
 * LA CLASE QUE LLAME A ESTE METODO TIENE LA RESPONSABILIDAD DE BORRAR EL ARCHIVO DE TEXTO
 */
string Huffman::encode(string file){

}