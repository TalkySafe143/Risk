//
// Created by talkysafe143 on 1/10/23.
//

#include "Risk.h"
#include "Grafo.cpp"

 list<Jugador> Risk::getJugadores()  {
    return jugadores;
}

void Risk::setJugadores(const list<Jugador> &jugadores) {
    Risk::jugadores = jugadores;
}

 list<Continente> &Risk::getContinentes()  {
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
    cout << "Inicializando...\n";
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

        for (Continente &continente: Risk::continentes) {
            if (continente.getId() == nuevo.getIdContinente()) {
                continente.agregarTerritorio(nuevo);
                break;
            }
        }
    }
    int continents = 0;
    for (; continents < 6; continents++) {
        auto contiIt = Risk::continentes.begin();
        if (continents == 0) {
            advance(contiIt, 1);
        } else if (continents == 1) {
            advance(contiIt, 0);
        } else if (continents == 2) {
            advance(contiIt, 3);
        } else if (continents == 3) {
            advance(contiIt, 5);
        } else if (continents == 4) {
            advance(contiIt, 2);
        } else if (continents == 5) {
            advance(contiIt, 4);
        }


        for (auto &terrCont: contiIt->getTerritorios()) {
            //cout << "Agregado " << terrCont.getNombre() << " con index " << n << endl;
            grafo.InsVertice(terrCont);
            //n++;
        }
    }
    //crear aristas
    //america del norte : 1
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




    //crear grafo
    //america del sur : 2
    /*grafo.InsVertice(1); //0
    grafo.InsVertice(2); //1
    grafo.InsVertice(3); //2
    grafo.InsVertice(4); //3
    //america del norte : 1
    grafo.InsVertice(3); //4
    grafo.InsVertice(4); //5
    grafo.InsVertice(9); //6
    grafo.InsVertice(2); //7
    grafo.InsVertice(7); //8
    grafo.InsVertice(8); //9
    grafo.InsVertice(1); //10
    grafo.InsVertice(6); //11
    grafo.InsVertice(5); //12
    //africa : 4
    grafo.InsVertice(5); //13
    grafo.InsVertice(3); //14
    grafo.InsVertice(1); //15
    grafo.InsVertice(2); //16
    grafo.InsVertice(6); //17
    grafo.InsVertice(4); //18
    //Australia : 6
    grafo.InsVertice(2); //19
    grafo.InsVertice(3); //20
    grafo.InsVertice(4); //21
    grafo.InsVertice(1); //22
    //Europa : 3
    grafo.InsVertice(2); //23
    grafo.InsVertice(1); //24
    grafo.InsVertice(4); //25
    grafo.InsVertice(7); //26
    grafo.InsVertice(3); //27
    grafo.InsVertice(6); //28
    grafo.InsVertice(5); //29
    //Europa : 5
    grafo.InsVertice(11); //30
    grafo.InsVertice(1); //31
    grafo.InsVertice(7); //32
    grafo.InsVertice(10); //33
    grafo.InsVertice(2); //34
    grafo.InsVertice(3); //35
    grafo.InsVertice(12); //36
    grafo.InsVertice(4); //37
    grafo.InsVertice(8); //38
    grafo.InsVertice(9); //39
    grafo.InsVertice(6); //40
    grafo.InsVertice(5); //41*/
    //america del sur
    grafo.InsArco(0, 2, 1); grafo.InsArco(2, 0, 1);
    grafo.InsArco(0, 1, 1); grafo.InsArco(1, 0, 1);
    grafo.InsArco(1, 3, 1); grafo.InsArco(3, 1, 1);
    grafo.InsArco(2, 3, 1); grafo.InsArco(3, 2, 1);
    grafo.InsArco(1, 2, 1); grafo.InsArco(2, 1, 1);
    //america del norte
    grafo.InsArco(3, 4, 1); grafo.InsArco(4, 3, 1);
    grafo.InsArco(4, 6, 1); grafo.InsArco(6, 4, 1);
    grafo.InsArco(4, 5, 1); grafo.InsArco(5, 4, 1);
    grafo.InsArco(6, 5, 1); grafo.InsArco(5, 6, 1);
    grafo.InsArco(6, 7, 1); grafo.InsArco(7, 6, 1);
    grafo.InsArco(0, 1, 1); grafo.InsArco(1, 0, 1);
    grafo.InsArco(5, 8, 1); grafo.InsArco(8, 5, 1);
    grafo.InsArco(5, 9, 1); grafo.InsArco(9, 5, 1);
    grafo.InsArco(7, 8, 1); grafo.InsArco(8, 7, 1);
    grafo.InsArco(8, 9, 1); grafo.InsArco(9, 8, 1);
    grafo.InsArco(7, 10, 1); grafo.InsArco(10, 7, 1);
    grafo.InsArco(8, 11, 1); grafo.InsArco(11 ,8, 1);
    grafo.InsArco(8, 12, 1); grafo.InsArco(12, 8, 1);
    grafo.InsArco(9, 12, 1); grafo.InsArco(12, 9, 1);
    grafo.InsArco(10, 11, 1); grafo.InsArco(11, 10, 1);
    grafo.InsArco(11, 12, 1); grafo.InsArco(12, 11, 1);
    //Africa
    grafo.InsArco(1, 13, 1); grafo.InsArco(13, 1, 1); // Se conecta con brasil
    grafo.InsArco(13, 14, 1); grafo.InsArco(14, 13, 1);
    grafo.InsArco(13, 15, 1); grafo.InsArco(15, 13, 1);
    grafo.InsArco(14, 16, 1); grafo.InsArco(16, 14, 1);
    grafo.InsArco(13, 16, 1); grafo.InsArco(16, 13, 1);
    grafo.InsArco(15, 16, 1); grafo.InsArco(16, 15, 1);
    grafo.InsArco(15, 17, 1); grafo.InsArco(17, 15, 1);
    grafo.InsArco(16, 18, 1); grafo.InsArco(18, 16, 1);
    grafo.InsArco(16, 17, 1); grafo.InsArco(17, 16, 1);
    grafo.InsArco(17, 18, 1); grafo.InsArco(18, 17, 1);
    //Australia
    grafo.InsArco(19, 20, 1); grafo.InsArco(20, 19, 1);
    grafo.InsArco(19, 21, 1); grafo.InsArco(21, 19, 1);
    grafo.InsArco(21, 20, 1); grafo.InsArco(20, 21, 1);
    grafo.InsArco(20, 22, 1); grafo.InsArco(22, 20, 1);
    grafo.InsArco(21, 22, 1); grafo.InsArco(22, 21, 1);
    //Europa
    grafo.InsArco(12, 23, 1); grafo.InsArco(23, 12, 1);
    grafo.InsArco(23, 24, 1); grafo.InsArco(24, 23, 1);
    grafo.InsArco(23, 25, 1); grafo.InsArco(25, 23, 1);
    grafo.InsArco(24, 26, 1); grafo.InsArco(26, 24, 1);
    grafo.InsArco(24, 27, 1); grafo.InsArco(27, 24, 1);
    grafo.InsArco(25, 27, 1); grafo.InsArco(27, 25, 1);
    grafo.InsArco(25, 28, 1); grafo.InsArco(28, 25, 1);
    grafo.InsArco(26, 27, 1); grafo.InsArco(27, 26, 1);
    grafo.InsArco(27, 28, 1); grafo.InsArco(28, 27, 1);
    grafo.InsArco(26, 29, 1); grafo.InsArco(29, 26, 1);
    grafo.InsArco(27, 29, 1); grafo.InsArco(29, 27, 1);
    grafo.InsArco(13, 26, 1); grafo.InsArco(26, 13, 1);
    grafo.InsArco(13, 29, 1); grafo.InsArco(29, 13, 1);
    grafo.InsArco(14, 29, 1); grafo.InsArco(29, 14, 1);
    //Asia
    grafo.InsArco(28, 30, 1); grafo.InsArco(30, 28, 1);
    grafo.InsArco(28, 31, 1); grafo.InsArco(31, 28, 1);
    grafo.InsArco(28, 32, 1); grafo.InsArco(32, 28, 1);
    grafo.InsArco(29, 32, 1); grafo.InsArco(32, 29, 1);
    grafo.InsArco(14, 32, 1); grafo.InsArco(32, 14, 1);
    grafo.InsArco(32, 31, 1); grafo.InsArco(31, 32, 1);
    grafo.InsArco(31, 30, 1); grafo.InsArco(30, 31, 1);
    grafo.InsArco(30, 33, 1); grafo.InsArco(33, 30, 1);
    grafo.InsArco(30, 34, 1); grafo.InsArco(34, 30, 1);
    grafo.InsArco(31, 35, 1); grafo.InsArco(35, 31, 1);
    grafo.InsArco(32, 35, 1); grafo.InsArco(35, 32, 1);
    grafo.InsArco(35, 34, 1); grafo.InsArco(34, 35, 1);
    grafo.InsArco(35, 39, 1); grafo.InsArco(39, 35, 1);
    grafo.InsArco(39, 34, 1); grafo.InsArco(34, 39, 1);
    grafo.InsArco(34, 33, 1); grafo.InsArco(33, 34, 1);
    grafo.InsArco(34, 38, 1); grafo.InsArco(38, 34, 1);
    grafo.InsArco(33, 38, 1); grafo.InsArco(38, 33, 1);
    grafo.InsArco(33, 37, 1); grafo.InsArco(37, 33, 1);
    grafo.InsArco(33, 36, 1); grafo.InsArco(36, 33, 1);
    grafo.InsArco(38, 39, 1); grafo.InsArco(39, 38, 1);
    grafo.InsArco(37, 36, 1); grafo.InsArco(36, 37, 1);
    grafo.InsArco(36, 40, 1); grafo.InsArco(40, 36, 1);
    grafo.InsArco(37, 40, 1); grafo.InsArco(40, 37, 1);
    grafo.InsArco(38, 40, 1); grafo.InsArco(40, 38, 1);
    grafo.InsArco(38, 41, 1); grafo.InsArco(41, 38, 1);
    grafo.InsArco(40, 41, 1); grafo.InsArco(41, 40, 1);

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

Jugador Risk::avanzarTurno(int move) {
    advance(Risk::turno, move);
    if (Risk::turno == Risk::jugadores.end()) Risk::turno = Risk::jugadores.begin();
    return *(Risk::turno);
}
