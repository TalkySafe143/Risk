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

int inicializarDatos() {
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
            i++:
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

list<Jugador> inicializarJugadores(string file) {
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

void iniciarJuego(list<Jugador> jugadores) {
    Risk::jugadores = jugadores;
    Risk::turno = Risk::jugadores.begin();
}

list<int> tirarDados(int numDados) {
    // Verifica que el número de dados sea válido (1-3 para ataque, 1-2 para defensa)
    if (numDados < 1 || numDados > 3) {
        cout << "Numero de dados no valido." << endl;
        return list<int>(); // Retorna una lista vacía si el número de dados no es válido
    }

    // Crear un generador de números aleatorios
    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister 19937 generator, gen(rd()) se usa para sembrar el generador
    uniform_int_distribution<> distrib(1, 6); // define el rango

    list<int> resultados;

    for (int i = 0; i < numDados; ++i) {
        resultados.push_back(distrib(gen)); // genera un número aleatorio y lo agrega a la lista
    }


    resultados.sort();
    resultados.reverse(); // esto pondrá los números más grandes primero

    return resultados;
}
int Risk::reasignarTropas() {
    // El jugador actual está referenciado por el iterador 'turno'.
    Jugador& jugadorActual = *turno;

    // Calcular tropas basadas en territorios.
    int numTerritorios = jugadorActual.getTerritorios().size();
    int tropasPorTerritorios = max(3, numTerritorios / 3); // Un jugador recibe la mayor cantidad entre 3 o un tercio de sus territorios.

    // Calcular tropas adicionales por continentes controlados.
    int tropasPorContinentes = 0;
    for (const Continente& continente : continentes) {
        bool controlaContinente = true;
        for (const Territorio& territorio : continente.getTerritorios()) {
            if (find_if(jugadorActual.getTerritorios().begin(), jugadorActual.getTerritorios().end(),
                        [&territorio](const Territorio& t) { return t.getIdTerritorio() == territorio.getIdTerritorio(); }) == jugadorActual.getTerritorios().end()) {
                controlaContinente = false;
                break;
            }
        }

        if (controlaContinente) {
            // Aquí, debes conocer la cantidad de tropas adicionales que un continente proporciona.
            // Esto debería ser un atributo de tus objetos Continente. Asumiendo que existe una función 'getTropasAdicionales'.
            tropasPorContinentes += continente.getTerritorios();
        }
    }

    return tropasPorTerritorios + tropasPorContinentes;
}

int fortificarTerritorio(Territorio from, Territorio to, int tropas) {
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

Jugador avanzarTurno() {
    Risk::turno++;
    if (Risk::turno == Risk::jugadores.end()) Risk::turno = Risk::jugadores.begin();
    return *(Risk::turno);
}
