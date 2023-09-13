#ifndef PROYECTO_JUGADOR_H
#define PROYECTO_JUGADOR_H
#include "Carta.h"
#include "Tropa.h"
#include "Territorio.h"
#include <list>
class Jugador {
private:
    list<Carta> cartas;
    list<Tropa> tropas;
    list<Territorio> territorios;
    string id;
    string nombre;
public:
    [[nodiscard]] const list<Carta> &getCartas() const;

    void setCartas(const list<Carta> &cartas);

    [[nodiscard]] const list<Tropa> &getTropas() const;

    void setTropas(const list<Tropa> &tropas);

    [[nodiscard]] const list<Territorio> &getTerritorios() const;

    void setTerritorios(const list<Territorio> &territorios);

    [[nodiscard]] const string &getId() const;

    void setId(const string &id);

    [[nodiscard]] const string &getNombre() const;

    void setNombre(const string &nombre);
};


#endif //PROYECTO_JUGADOR_H
