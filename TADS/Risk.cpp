//
// Created by talkysafe143 on 1/10/23.
//

#include "Risk.h"
#include "Grafo.cpp"

list<Jugador> &Risk::getJugadores()  {
    return jugadores;
}

void Risk::setJugadores(const list<Jugador> &jugadores) {
    Risk::jugadores = jugadores;
}

 list<Continente> &Risk::getContinentes()  {
    return continentes;
}

void Risk::setContinentes(list<Continente> &continentes) {
    Risk::continentes = continentes;
}

list<Carta> &Risk::getCartas() {
    return cartas;
}

void Risk::setCartas( list<Carta> &cartas) {
    Risk::cartas = cartas;
}

list<Jugador>::iterator &Risk::getTurno() {
    return turno;
}

void Risk::setTurno(const list<Jugador>::iterator &turno) {
    Risk::turno = turno;
}

int Risk::inicializarDatos() {
    cout << "Inicializando...\n";
    Risk::gruposCartasIntercambiados = 0;
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

    ifstream continentess("../Data/Continentes.csv");
    list<Continente> nuevosContinentes;

    if (!continentess) return -1;

    getline(continentess, line); // Lineas de instrucciones

    while (getline(continentess, line)) {
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

    continentess.close();

    ifstream territorios("../Data/Territorios.csv");

    if (!territorios) return -1;

    getline(territorios, line);

    int n = 0;

    while (getline(territorios, line)) {
        auto *nuevo = new Territorio();
        int i = 1;
        string token;
        istringstream ss(line);

        while (getline(ss, token, ';')) {
            if (i == 1) nuevo->setIdTerritorio(token);
            if (i == 2) nuevo->setIdContinente(token);
            if (i == 4) nuevo->setNombre(token);
            i++;
        }

        for (Continente &continente: Risk::continentes) {
            if (continente.getId() == nuevo->getIdContinente()) {
                continente.agregarTerritorio(*nuevo);
                grafo.InsVertice(*nuevo);
                break;
            }
        }
    }

    grafo.InsArco(0, 7, 1); grafo.InsArco(7, 0, 1);
    grafo.InsArco(7, 4, 1); grafo.InsArco(4, 7, 1);
    grafo.InsArco(0, 1, 1); grafo.InsArco(1, 0, 1);
    grafo.InsArco(1, 7, 1); grafo.InsArco(7, 1, 1);
    grafo.InsArco(5, 7, 1); grafo.InsArco(7, 5, 1);
    grafo.InsArco(5, 4, 1); grafo.InsArco(4, 5, 1);
    grafo.InsArco(6, 4, 1); grafo.InsArco(4, 6, 1);
    grafo.InsArco(1, 5, 1); grafo.InsArco(5, 1, 1);
    grafo.InsArco(5, 6, 1); grafo.InsArco(6, 5, 1);
    grafo.InsArco(2, 1, 1); grafo.InsArco(1, 2, 1);
    grafo.InsArco(2, 5, 1); grafo.InsArco(5, 2, 1);
    grafo.InsArco(3, 5, 1); grafo.InsArco(5, 3, 1);
    grafo.InsArco(3, 6, 1); grafo.InsArco(6, 3, 1);
    grafo.InsArco(2, 3, 1); grafo.InsArco(3, 2, 1);
    grafo.InsArco(8, 2, 1); grafo.InsArco(2, 8, 1);
    grafo.InsArco(8, 3, 1); grafo.InsArco(3, 8, 1);
    //america del norte - america del sur
    grafo.InsArco(8, 12, 1); grafo.InsArco(12, 8, 1);
    //america del sur : 2
    grafo.InsArco(12, 11, 1); grafo.InsArco(11, 12, 1);
    grafo.InsArco(12, 10, 1); grafo.InsArco(10, 12, 1);
    grafo.InsArco(11, 10, 1); grafo.InsArco(10, 11, 1);
    grafo.InsArco(11, 9, 1); grafo.InsArco(9, 11, 1);
    grafo.InsArco(10, 9, 1); grafo.InsArco(9, 10, 1);
    //europa - america del norte
    grafo.InsArco(4, 18, 1); grafo.InsArco(18, 4, 1);
    //europa : 3
    grafo.InsArco(18, 13, 1); grafo.InsArco(13, 18, 1);
    grafo.InsArco(18, 17, 1); grafo.InsArco(17, 18, 1);
    grafo.InsArco(17, 13, 1); grafo.InsArco(13, 17, 1);
    grafo.InsArco(17, 16, 1); grafo.InsArco(16, 17, 1);
    grafo.InsArco(17, 14, 1); grafo.InsArco(14, 17, 1);
    grafo.InsArco(13, 14, 1); grafo.InsArco(14, 13, 1);
    grafo.InsArco(13, 19, 1); grafo.InsArco(19, 13, 1);
    grafo.InsArco(16, 14, 1); grafo.InsArco(14, 16, 1);
    grafo.InsArco(14, 19, 1); grafo.InsArco(19, 14, 1);
    grafo.InsArco(16, 15, 1); grafo.InsArco(15, 16, 1);
    grafo.InsArco(14, 15, 1); grafo.InsArco(15, 14, 1);
    grafo.InsArco(19, 15, 1); grafo.InsArco(15, 19, 1);
    //europa - africa
    grafo.InsArco(20, 16, 1); grafo.InsArco(16, 20, 1);
    grafo.InsArco(20, 15, 1); grafo.InsArco(15, 20, 1);
    grafo.InsArco(24, 15, 1); grafo.InsArco(15, 24, 1);
    //america del sur - africa
    grafo.InsArco(10, 20, 1); grafo.InsArco(20, 10, 1);
    //africa : 4
    grafo.InsArco(20, 24, 1); grafo.InsArco(24, 20, 1);
    grafo.InsArco(20, 23, 1); grafo.InsArco(23, 20, 1);
    grafo.InsArco(20, 22, 1); grafo.InsArco(22, 20, 1);
    grafo.InsArco(24, 22, 1); grafo.InsArco(22, 24, 1);
    grafo.InsArco(23, 22, 1); grafo.InsArco(22, 23, 1);
    grafo.InsArco(23, 21, 1); grafo.InsArco(21, 23, 1);
    grafo.InsArco(22, 21, 1); grafo.InsArco(21, 22, 1);
    grafo.InsArco(22, 25, 1); grafo.InsArco(25, 22, 1);
    grafo.InsArco(21, 25, 1); grafo.InsArco(25, 21, 1);
    //asia - europa
    grafo.InsArco(36, 19, 1); grafo.InsArco(19, 36, 1);
    grafo.InsArco(26, 19, 1); grafo.InsArco(19, 26, 1);
    grafo.InsArco(32, 19, 1); grafo.InsArco(19, 32, 1);
    grafo.InsArco(32, 15, 1); grafo.InsArco(15, 32, 1);
    //asia africa
    grafo.InsArco(32, 24, 1); grafo.InsArco(24, 32, 1);
    //asia : 5
    grafo.InsArco(36, 35, 1); grafo.InsArco(35, 36, 1);
    grafo.InsArco(36, 27, 1); grafo.InsArco(27, 36, 1);
    grafo.InsArco(26, 27, 1); grafo.InsArco(27, 26, 1);
    grafo.InsArco(26, 28, 1); grafo.InsArco(28, 26, 1);
    grafo.InsArco(32, 28, 1); grafo.InsArco(28, 32, 1);
    grafo.InsArco(32, 26, 1); grafo.InsArco(26, 32, 1);
    grafo.InsArco(26, 36, 1); grafo.InsArco(36, 26, 1);
    grafo.InsArco(28, 27, 1); grafo.InsArco(27, 28, 1);
    grafo.InsArco(27, 35, 1); grafo.InsArco(35, 27, 1);
    grafo.InsArco(27, 34, 1); grafo.InsArco(34, 27, 1);
    grafo.InsArco(27, 33, 1); grafo.InsArco(33, 27, 1);
    grafo.InsArco(33, 35, 1); grafo.InsArco(35, 33, 1);
    grafo.InsArco(33, 29, 1); grafo.InsArco(29, 33, 1);
    grafo.InsArco(33, 31, 1); grafo.InsArco(31, 33, 1);
    grafo.InsArco(33, 30, 1); grafo.InsArco(30, 33, 1);
    grafo.InsArco(35, 29, 1); grafo.InsArco(29, 35, 1);
    grafo.InsArco(35, 37, 1); grafo.InsArco(37, 35, 1);
    grafo.InsArco(29, 37, 1); grafo.InsArco(37, 29, 1);
    grafo.InsArco(19, 31, 1); grafo.InsArco(31, 29, 1);
    grafo.InsArco(37, 31, 1); grafo.InsArco(31, 37, 1);
    grafo.InsArco(31, 30, 1); grafo.InsArco(30, 31, 1);
    //autralia - asia
    grafo.InsArco(34, 40, 1); grafo.InsArco(40, 34, 1);
    //Australia : 6
    grafo.InsArco(40, 41, 1); grafo.InsArco(41, 40, 1);
    grafo.InsArco(40, 38, 1); grafo.InsArco(38, 40, 1);
    grafo.InsArco(41, 38, 1); grafo.InsArco(38, 41, 1);
    grafo.InsArco(41, 39, 1); grafo.InsArco(38, 39, 1);
    grafo.InsArco(36, 35, 1); grafo.InsArco(35, 36, 1);

    territorios.close();

    return 1;
}

list<Jugador> *Risk::inicializarJugadores(string file) {
    auto *result = new list<Jugador>();
    ifstream input(file);

    if (!input) return result;

    string line;

    input >> line;

    int numJugadores = stoi(line);

    for (int i = 0; i < numJugadores; i++) {
        Jugador jug;

        jug.setId(to_string(i));
        getline(input, line, ';');
        jug.setNombre(line);
        getline(input, line, ';');
        jug.setColor(line);
        getline(input, line, ';');
        int numTerritorios = stoi(line);

        list<Territorio> jugTerr;
        for (int j = 0; j < numTerritorios; j++) {
            string id;
            getline(input, line, ';');
            id = line;
            getline(input, line, ';');
            int tropas = stoi(line);

            for (Continente &cont: Risk::continentes) { //encuentra el territorio en el continente
                Territorio &terr = cont.encontrarTerritorio(id);
                if (terr.getNombre() == "-1") continue;
                terr.setTropas(tropas);

                // Obtener todos los sucesores del territorio
                auto &vertexs = Risk::grafo.getVerticesNode();
                int u = 0;
                for (auto &someTerr: vertexs) {
                    if (terr == someTerr.getData()) {
                        someTerr.getData().setTropas(tropas);
                        break;
                    }
                    u++;
                }

                auto neighboors = Risk::grafo.sucesores(u);

                for (int v: neighboors) {
                    Risk::grafo.changeArcCost(v, u, tropas);
                }

                jugTerr.push_back(terr);
                break;
            }
        }

        getline(input, line);
        int numCartas = stoi(line); // Sin usar?

        jug.setTerritorios(jugTerr);
        result->push_back(jug);
    }

    return result;
}
list<int> tirarDados(int numDados) {
    // Verifica que el número de dados sea válido (1-3 para ataque, 1-2 para defensa)
    if (numDados < 1 || numDados > 3) {
        cout << "Numero de dados no valido." << endl;
        return list<int>(); // Retorna una lista vacía si el número de dados no es válido
    }

    // Inicializa la semilla de los números aleatorios una sola vez.
    static bool initialized = false;
    if (!initialized) {
        srand(time(nullptr)); // Utiliza el tiempo actual como semilla.
        initialized = true;
    }

    list<int> resultados;

    for (int i = 0; i < numDados; ++i) {
        resultados.push_back(rand() % 6 + 1); // genera un número aleatorio entre 1 y 6 y lo agrega a la lista
    }

    resultados.sort();
    resultados.reverse(); // Esto pondrá los números más grandes primero.

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

void Risk::iniciarJuego(list<Jugador> &jugadores) {
    Risk::jugadores = jugadores;
    Risk::turno = Risk::jugadores.begin();
}


int Risk::reasignarTropas() {
    // El jugador actual está referenciado por el iterador 'turno'.
    Jugador& jugadorActual = *turno;

    // Calcular tropas basadas en territorios.
    int numTerritorios = (int)jugadorActual.getTerritorios().size();
    int tropasPorTerritorios = numTerritorios / 3; // Un jugador recibe la mayor cantidad entre 3 o un tercio de sus territorios.

    // Calcular tropas adicionales por continentes controlados.
    int tropasPorContinentes = 0;

    auto poderContinentes = jugadorActual.verificarContinentes(Risk::continentes);

    for (auto &cont: poderContinentes) {
        if (cont.getNombre() =="America del Norte") tropasPorContinentes += 5;
        if (cont.getNombre() =="America del Sur") tropasPorContinentes += 2;
        if (cont.getNombre() =="Europa") tropasPorContinentes += 5;
        if (cont.getNombre() =="Africa") tropasPorContinentes += 3;
        if (cont.getNombre() =="Asia") tropasPorContinentes += 7;
        if (cont.getNombre() =="Australia") tropasPorContinentes += 2;
    }

    return tropasPorTerritorios + tropasPorContinentes;
}
bool Risk::esCombinacionValida(std::list<Carta>& cartas) {
    // Supongamos que 'tipo' es un miembro de 'Carta' que indica si es de infantería, caballería, artillería o comodín.
    int infanteria = 0, caballeria = 0, artilleria = 0, comodines = 0;
    for (Carta& carta : cartas) {
        if (carta.getValue() == 1) ++infanteria;
        else if (carta.getValue() == 5) ++caballeria;
        else if (carta.getValue() == 10) ++artilleria;
        else if (carta.getIdTerritorio() == "-1") ++comodines;
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

int Risk::intercambiarCartas() {
    int unidades = 0;

    auto &cartas = Risk::turno->getCartas();

    if (cartas.size() >= 3 && esCombinacionValida(cartas)) {
        // Calcula las unidades adicionales basadas en la cantidad de intercambios realizados previamente
        if (gruposCartasIntercambiados < 5) {
            unidades += 4 + gruposCartasIntercambiados * 2;
        } else {
            unidades += 15 + (gruposCartasIntercambiados - 5) * 5;
        }

        for (auto &carta: Risk::turno->getCartas()) {
            Risk::cartas.push_back(carta);
        }

        Risk::turno->getCartas().clear();

        // Retira las cartas utilizadas para el intercambio
        //retirarCartasUtilizadas(cartas, territorios);

        // Incrementa el contador de grupos intercambiados
        Risk::gruposCartasIntercambiados++;
    }

    return unidades;
}
int Risk::fortificarTerritorio(Territorio &from, Territorio &to, int tropas) {
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

Jugador Risk::avanzarTurno(int move) {
    advance(Risk::turno, move);
    if (Risk::turno == Risk::jugadores.end()) Risk::turno = Risk::jugadores.begin();
    return *(Risk::turno);
}
Grafo<Territorio> &Risk::getGrafo() {
    return Risk::grafo;
}

list<int> Risk::tirarDados(int numDados) {
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