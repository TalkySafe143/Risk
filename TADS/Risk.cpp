//
// Created by talkysafe143 on 1/10/23.
//

#include "Risk.h"

const list<Jugador> &Risk::getJugadores() const {
    return jugadores;
}

void Risk::setJugadores(const list<Jugador> &jugadores) {
    Risk::jugadores = jugadores;
}

const list<Continente> &Risk::getContinentes() const {
    return continentes;
}

void Risk::setContinentes(const list<Continente> &continentes) {
    Risk::continentes = continentes;
}

list<Carta> Risk::getCartas() {
    return cartas;
}

void Risk::setCartas(const list<Carta> &cartas) {
    Risk::cartas = cartas;
}

const list<Jugador>::iterator &Risk::getTurno() const {
    return turno;
}

void Risk::setTurno(const list<Jugador>::iterator &turno) {
    Risk::turno = turno;
}

int Risk::inicializarDatos() {
    ifstream cards("../Data/Cards.csv");
    list<Carta> nuevasCartas;

    if (!cards) return -1;

    string line;

    getline(cards, line);

    while (getline(cards, line)) {
        Carta nueva;
        string token;
        int i = 1;
        istringstream ss(line);
        while (getline(ss, token, ';')) {
            if (i == 1) nueva.setId(token);
            if (i == 2) {
                if (token == "TR") nueva.setComodin(false);
                else nueva.setComodin(true);
            }
            if (i == 3) nueva.setIdTerritorio(token);
            if (i == 4) {
                int value = 0;
                if (token == " Soldier") value = 1;
                if (token == " Horse") value = 5;
                if (token == " Canon" || token == "Las Tres") value = 10;
                nueva.setValue(value);
            }
            i++;
        }
        nuevasCartas.push_back(nueva);
    }

    Risk::setCartas(nuevasCartas);

    cards.close();

    ifstream continentes("../Data/Continentes.csv");
    list<Continente> nuevosContinentes;

    if (!continentes) return -1;

    getline(continentes, line); // Lineas de instrucciones

    while (getline(continentes, line)) {
        Continente cont;
        string token;
        int i = 1;
        istringstream ss(line);

        while (getline(ss, token, ';')) {
            if (i == 1) cont.setId(token);
            if (i == 2) cont.setNombre(token);
            i++;
        }

        nuevosContinentes.push_back(cont);
    }

    Risk::setContinentes(nuevosContinentes);

    continentes.close();

    ifstream territorios("../Data/Territorios.csv");

    if (!territorios) return -1;

    getline(territorios, line);

    while (getline(territorios, line)) {
        Territorio nuevo;
        int i = 1;
        string token;
        istringstream ss(line);

        while (getline(ss, token, ';')) {
            if (i == 1) nuevo.setIdTerritorio(token);
            if (i == 2) nuevo.setIdContinente(token);
            if (i == 4) nuevo.setNombre(token);
            i++;
        }

        for (Continente continente: Risk::continentes) {
            if (continente.getId() == nuevo.getIdContinente()) {
                continente.agregarTerritorio(nuevo);
                break;
            }
        }
    }

    territorios.close();

    return 1;
}

list<Jugador> Risk::inicializarJugadores(string file) {
    list<Jugador> result;
    ifstream input(file);

    if (!input) return result;

    string line;

    input >> line;

    int numJugadores = stoi(line);

    for (int i = 0; i < numJugadores; i++) {
        Jugador jug;

        jug.setId(to_string(i+1));
        getline(input, line, ';');
        jug.setNombre(line);
        getline(input, line, ';');
        jug.setColor(line);
        getline(input, line, ';');
        int numTerritorios = stoi(line);

        list<Territorio> jugTerr;
        for (int j = 0; j < numTerritorios; j++) {
            string id, tropas;
            getline(input, line, ';');
            id = line;
            getline(input, line, ';');
            tropas = stoi(line);

            for (Continente cont: Risk::continentes) {
                Territorio terr = cont.encontrarTerritorio(id);
                if (terr.getNombre() == "-1") continue;
                jugTerr.push_back(terr);
                break;
            }
        }

        getline(input, line, ';');
        int numCartas = stoi(line); // Sin usar?

        jug.setTerritorios(jugTerr);
        result.push_back(jug);
    }

    return result;
}

void Risk::iniciarJuego(list<Jugador> jugadores) {
    Risk::jugadores = jugadores;
    Risk::turno = Risk::jugadores.begin();
}

int Risk::fortificarTerritorio(Territorio from, Territorio to, int tropas) {
    list<Territorio>::iterator fromIt = Risk::turno->getTerritorios().begin();
    list<Territorio>::iterator toIt = Risk::turno->getTerritorios().begin();
    bool fromFounded = false, toFounded = false;
    while (
           fromIt != Risk::turno->getTerritorios().end() &&
           toIt != Risk::turno->getTerritorios().end()
    ) {
        if (fromIt->getIdTerritorio() == from.getIdTerritorio()) fromFounded = true;
        if (toIt->getIdTerritorio() == to.getIdTerritorio()) toFounded = true;

        if (toFounded && fromFounded) break;

        if (!toFounded) toIt++;
        if (!fromFounded) fromIt++;
    }

    if (
        fromIt == Risk::turno->getTerritorios().end() ||
           toIt == Risk::turno->getTerritorios().end()
    ) return -1;

    if (fromIt->getTropas() < tropas) return -1;

    fromIt->setTropas(fromIt->getTropas() - tropas);

    toIt->setTropas(toIt->getTropas() + tropas);

    return 1;
}

Jugador Risk::avanzarTurno() {
    Risk::turno++;
    if (Risk::turno == Risk::jugadores.end()) Risk::turno = Risk::jugadores.begin();
    return *(Risk::turno);
}
