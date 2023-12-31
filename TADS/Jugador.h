#ifndef PROYECTO_JUGADOR_H
#define PROYECTO_JUGADOR_H
#include "Carta.h"
#include "Territorio.h"
#include "Continente.h"
#include <list>
#include "Utils.h"
class Jugador {
private:
    list<Carta> cartas;
    list<Territorio> territorios;
    string id;
    string nombre;
    string color;
public:

    list<Carta> &getCartas();
    void setCartas(const list<Carta> &cartas);

    void agregarCarta(const Carta carta);

    list<Territorio> &getTerritorios();

    void setTerritorios(const list<Territorio> &territorios);

    void agregarTerritorio(Territorio nuevo);

    string getId();

    void setId(const string &id);

    string getNombre();

    void setNombre(const string &nombre);

    const string &getColor() const;

    void setColor(const string &color);

    /**
     * Esta funcion tiene como proposito verificar cuantos continentes completos tiene ocupado el jugador
     * @param base Lista de continentes base para verificar
     * @return La lista de continentes que tiene totalmente ocupados el jugador
     */
    list<Continente> verificarContinentes(list<Continente> base);

    /**
     * Esta funcion tiene como proposito agregar/eliminar un numero de tropas a un territorio en especifico
     * @param field El territorio que se va a afectar
     * @param num El numero de tropas a afectar (+ para agregar / - para eliminar)
     * @return Un codigo de estado
     *      - 1: Todo salio bien
     *      - -1: Algo salio mal
     */
    int modificarTropasTerritorio(Territorio field, int num); // Codigo de estado
};


#endif //PROYECTO_JUGADOR_H
