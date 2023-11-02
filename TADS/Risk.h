//
// Created by talkysafe143 on 1/10/23.
//

#ifndef PROYECTO_RISK_H
#define PROYECTO_RISK_H

#include <iostream>
#include <list>
#include "Jugador.h"
#include "Carta.h"
#include "Continente.h"
#include <sstream>

using namespace std;

class Risk {
private:
    list<Jugador> jugadores;
    list<Continente> continentes;
    static list<Carta> cartas;
    list<Jugador>::iterator turno; // Se usa internamente en varios metodos
public:
    /**
     * Esta funcion tiene como proposito inicializar los datos de los continentes
     * territorios y cartas descritos para el juego
     *
     * @return Un codigo de estado
     *       1: Todo salio bien
     *      -1: Algo salio mal
     */
    int inicializarDatos();

    /**
     * Esta funcion tiene como objetivo inicializar los jugadores desde un archivo
     * de configuracion
     * @param file El nombre del archivo de configuracion
     * @return Una lista de jugadores inicializados, en caso de que algo salga mal, retorna una lista vacia
    */
    list<Jugador> inicializarJugadores(string file);

    /**
     * Esta funcion tiene como proposito simular las jugadas desde un archivo
     * @param file El nombre del archivo de las jugadas
    */
    void simularJugadas(string file); // ?

    /**
     * Esta funcion tiene como proposito iniciar formalmente el juego con los jugadores
     * @param jugadores La lista de los jugadores del juego
     */
    void iniciarJuego(list<Jugador> jugadores);

    /**
     * Esta funcion tiene como proposito verificar cuantas tropas puede reclamar el turno actual
     * relacionado con el numero de territorios y continentes ocupados
     * @return La cantidad de tropas que el turno actual puede reclamar
     */
    int reasignarTropas();

    /**
     * Esta funcion tiene como proposito verificar cuantas tropas puede reclamar el turno actual
     * relacionado con las posibles combinaciones de las cartas que posea el jugador
     * @return La cantidad de cartas que el turno actual puede reclamar
     */
    int intercambiarCartas(); // Preguntar ¿grupos?

    /**
     * Esta funcion tiene como proposito obtener todos los territorios vecinos que puede
     * tener un territorio en especifico
     * @param search El territorio a obtener sus vecinos
     * @return Una lista de territorios vecinos del territorio pasado como parametro
     */
    list<Territorio> obtenerTerritoriosVecinos(Territorio search); // Grafos mejor

    /**
     * Esta funcion tiene como proposito simular una tirada de dados de la vida real
     * @param numDados El numero de dados a tirar
     * @return Una lista con los resultados aleatorios del numero de dados
     */
    list<int> tirarDados(int numDados);

    /**
     * Esta funcion tiene como proposito fortificar los territorios del turno actua
     * @param from Territorio de origen de las tropas
     * @param to Territorio de destino de las tropas
     * @param tropas Cantidad de tropas
     * @return Un codigo de estado
     *      - 1: Todo salio bien
     *      - -1: Algo salió mal
     */
    int fortificarTerritorio(Territorio from, Territorio to, int tropas);

    /**
     * El proposito de esta funcion es mover el iterador del turno y reacomodarlo segun la lista
     * de jugadores
     * @return El jugador el cual le corresponde el turno
     */
    Jugador avanzarTurno();

    bool esCombinacionValida(std::list<Carta>& cartas);

    void retirarCartasUtilizadas(std::list<Carta>& cartas, const std::list<Territorio>& territorios);

    const list<Jugador> &getJugadores() const;

    void setJugadores(const list<Jugador> &jugadores);

    const list<Continente> &getContinentes() const;

    void setContinentes(const list<Continente> &continentes);

    list<Carta> getCartas();

    static void setCartas(const list<Carta> &cartas);

    const list<Jugador>::iterator &getTurno() const;

    void setTurno(const list<Jugador>::iterator &turno);
};


#endif //PROYECTO_RISK_H
