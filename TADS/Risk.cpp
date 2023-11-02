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
void simularJugada(string jugada) {
    stringstream ss(jugada);
    string atacanteStr, defensorStr;

    getline(ss, atacanteStr, ':');
    getline(ss, defensorStr, ':');

    int atacante = stoi(atacanteStr); // Convertir string a int.
    int defensor = stoi(defensorStr); // Convertir string a int.

    // Limitar el número de dados de acuerdo a las reglas de Risk.
    atacante = min(atacante, 3);
    defensor = min(defensor, 2);

    // Lanzar dados.
    list<int> dadosAtacante = tirarDados(atacante);
    list<int> dadosDefensor = tirarDados(defensor);

    // Simular el combate.
    int ejercitosPerdidosAtacante = 0;
    int ejercitosPerdidosDefensor = 0;

    auto itAtacante = dadosAtacante.begin();
    auto itDefensor = dadosDefensor.begin();

    while (itAtacante != dadosAtacante.end() && itDefensor != dadosDefensor.end()) {
        if (*itAtacante > *itDefensor) {
            ejercitosPerdidosDefensor++;
        } else {
            ejercitosPerdidosAtacante++;
        }
        ++itAtacante;
        ++itDefensor;
    }

    // Mostrar los resultados.
    cout << "Atacante lanza: ";
    for (int dado : dadosAtacante) {
        cout << dado << " ";
    }

    cout << "\nDefensor lanza: ";
    for (int dado : dadosDefensor) {
        cout << dado << " ";
    }

    cout << "\nResultados: Atacante pierde " << ejercitosPerdidosAtacante
         << " ejércitos. Defensor pierde " << ejercitosPerdidosDefensor << " ejércitos.\n";
}

void simularJugadas(string file) {
    ifstream archivo(file);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << file << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string jugada;

        while (getline(ss, jugada, ';')) {
            simularJugada(jugada);
        }
    }

    archivo.close();
}

void iniciarJuego(list<Jugador> jugadores) {
    Risk::jugadores = jugadores;
    Risk::turno = Risk::jugadores.begin();
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
bool esCombinacionValida(std::list<Carta>& cartas) {
    // Supongamos que 'tipo' es un miembro de 'Carta' que indica si es de infantería, caballería, artillería o comodín.
    int infanteria = 0, caballeria = 0, artilleria = 0, comodines = 0;
    for (const Carta& carta : cartas) {
        if (carta.getId() == "infanteria") ++infanteria;
        else if (carta.getId() == "caballeria") ++caballeria;
        else if (carta.getId() == "artilleria") ++artilleria;
        else if (carta.getId() == "comodin") ++comodines;
    }

    // Verifica las combinaciones válidas
    if (comodines == 1) {
        // Si hay un comodín, solo necesitamos dos cartas del mismo tipo o todas diferentes.
        return (infanteria >= 2 || caballeria >= 2 || artilleria >= 2 ||
                (infanteria > 0 && caballeria > 0 && artilleria > 0));
    } else if (comodines == 0) {
        // Sin comodines, necesitamos tres cartas del mismo tipo o todas diferentes.
        return (infanteria == 3 || caballeria == 3 || artilleria == 3 ||
                (infanteria == 1 && caballeria == 1 && artilleria == 1));
    }

    return false;
}
void retirarCartasUtilizadas(std::list<Carta>& cartas, const std::list<Territorio>& territorios) {
    // Suponemos que 'cartas' contiene al menos 3 cartas que forman una combinación válida.

    // Contadores para las cartas de cada tipo.
    int infanteria = 0, caballeria = 0, artilleria = 0, comodines = 0;

    // Contar las cartas de cada tipo.
    for (const auto& carta : cartas) {
        if (carta.getId() == "Infanteria") infanteria++;
        else if (carta.getId() == "Caballeria") caballeria++;
        else if (carta.getId() == "Artilleria") artilleria++;
        else if (carta.getId() == "Comodin") comodines++;
    }

    // Determinar qué cartas retirar.
    std::list<Carta>::iterator it = cartas.begin();
    while (it != cartas.end()) {
        bool cartaEliminada = false;
        if (comodines > 0 && it->getId() == "Comodin") {
            // Eliminar un comodín.
            it = cartas.erase(it);
            comodines--;
            cartaEliminada = true;
        } else if (infanteria > 0 && it->getId() == "Infanteria") {
            // Eliminar una carta de infantería.
            it = cartas.erase(it);
            infanteria--;
            cartaEliminada = true;
        } else if (caballeria > 0 && it->getId() == "Caballeria") {
            // Eliminar una carta de caballería.
            it = cartas.erase(it);
            caballeria--;
            cartaEliminada = true;
        } else if (artilleria > 0 && it->getId() == "Artilleria") {
            // Eliminar una carta de artillería.
            it = cartas.erase(it);
            artilleria--;
            cartaEliminada = true;
        }

        // Si no se eliminó ninguna carta, avanzamos al siguiente elemento.
        if (!cartaEliminada) {
            ++it;
        }

        // Si hemos eliminado tres cartas, salimos del bucle.
        if ((3 - comodines - infanteria - caballeria - artilleria) >= 3) {
            break;
        }
    }
}
int intercambiarCartas(std::list<Carta>& cartas, const std::list<Territorio>& territorios, int& gruposIntercambiados) {
    int unidades = 0;

    if (cartas.size() >= 3 && esCombinacionValida(cartas)) {
        // Calcula las unidades adicionales basadas en la cantidad de intercambios realizados previamente
        if (gruposIntercambiados < 5) {
            unidades += 4 + gruposIntercambiados * 2;
        } else {
            unidades += 15 + (gruposIntercambiados - 5) * 5;
        }

        // Calcula las unidades extra por cartas que coinciden con territorios ocupados
        for (auto& carta : cartas) {
            if (std::any_of(territorios.begin(), territorios.end(), [&carta](const Territorio& territorio) {
                return carta.getIdTerritorio() == territorio.getNombre() && territorio.getTropas();
            })) {
                unidades += 2; // Asume que solo se cuentan una vez las unidades extras por cartas/territorios
            }
        }

        // Retira las cartas utilizadas para el intercambio
        retirarCartasUtilizadas(cartas, territorios);

        // Incrementa el contador de grupos intercambiados
        gruposIntercambiados++;
    }

    return unidades;
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
