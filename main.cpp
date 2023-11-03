#include <bits/stdc++.h>
#include "TADS/Interfaces.h"
#include "TADS/Huffman.h"
#include "TADS/Grafo.cpp"

using namespace std;

enum StringOptions {
    inicializar,
    turno,
    invalido,
    guardar,
    guardar_comprimido,
    inicializar_comprimido
};

StringOptions evalString(string a) {
    if (a == "inicializar") return inicializar;
    else if (a == "turno") return turno;
    else if (a == "guardar") return guardar;
    else if (a == "guardar_comprimido") return guardar_comprimido;
    else if (a == "inicializar_comprimido") return inicializar_comprimido;
    else return invalido;
}

int main() {
    system("ascii-image-converter title.png -f -b --dither -C");
    list<string> command;
    list<string>::iterator it;
    // inicializar
    Interfaces juego;
    Huffman saveGame;
    bool juegoIniciado = false;
    bool primerTurno = false;
    bool juegoFinalizado = false;
    do {
        cout << "Ingrese su comando: ";
        command.clear();
        char* str = new char[100];
        cin.getline(str, 50);

        char *p = strtok(str, " ");
        if (p != NULL) {
            while (p != NULL){
                command.push_back(p);
                p = strtok(NULL, " ");
            }
        } else {
            command.push_back(str);
        }
        it = command.begin();

        switch (evalString(*it)) {
            case inicializar: {

                if(!juegoIniciado){

                    if (!juego.getGame().inicializarDatos()) {
                        cout << "Algo salio mal inicializando los datos\n";
                        break;
                    }

                    int initOption = -1;
                    do {
                        cout << "¿Desea inicializarlo con un archivo?: [1 -> YES / 0 -> NO]: ";
                        cin >> initOption;
                    } while (initOption != 1 && initOption != 0);

                    if (initOption == 1) {
                        string fileName;
                        cout << "Escriba el nombre del archivo para inicializar el juego: ";
                        cin >> fileName;
                        juego.getGame().iniciarJuego(
                                juego.getGame().inicializarJugadores(fileName)
                                );
                    } else {
                        juego.inicializarJuego();
                    }
                    juegoIniciado = true;
                    cout << "(Inicialización satisfactoria) El juego se ha inicializado correctamente." << endl;
                }else{
                    cout << "(Juego en curso) El juego ya ha sido inicializado." << endl;
                }

                primerTurno = true;
                break;
            }
            case turno: {                      //turno <id_jugador>
                auto itTurno = command.begin();
                itTurno++;
                if (!primerTurno) {
                    juego.getGame().avanzarTurno(1);
                }

                if (juego.getGame().getTurno()->getId() != *itTurno) {
                    cout << "(Jugador fuera de turno) UPS, turno invalido\n";
                    if (!primerTurno) {
                        juego.getGame().avanzarTurno(-1);
                    }
                }

                primerTurno = false;

                cout << "---- Reasignar las tropas -----\n";

                int numeroTropasReclamadas = 0;

                numeroTropasReclamadas += juego.getGame().reasignarTropas();

                auto continentesJugador = juego.getGame().getTurno()->verificarContinentes(juego.getGame().getContinentes());

                for (auto cont: continentesJugador) {
                    if (cont.getId() == "1") numeroTropasReclamadas += 5;
                    if (cont.getId() == "2") numeroTropasReclamadas += 2;
                    if (cont.getId() == "3") numeroTropasReclamadas += 5;
                    if (cont.getId() == "4") numeroTropasReclamadas += 3;
                    if (cont.getId() == "5") numeroTropasReclamadas += 7;
                    if (cont.getId() == "6") numeroTropasReclamadas += 2;
                }

                //numeroTropasReclamadas += juego.getGame().intercambiarCartas();

                juego.asignarTropasTerritorio(numeroTropasReclamadas, *(juego.getGame().getTurno()));

                cout << "---- Atacar un territorio vecino ----\n";
                cout << "Seleccione un territorio desde el cual atacar\n";
                set<string> validIds;
                for (auto terr: juego.getGame().getTurno()->getTerritorios()) {
                    cout << terr.getIdTerritorio() << " -> " << terr.getNombre() << endl;
                    validIds.insert(terr.getIdTerritorio());
                }

                string optionTerr = "";

                while (!validIds.count(optionTerr)) {
                    cin >> optionTerr;

                    if (!validIds.count(optionTerr)) {
                        cout << "No posee ese territorio\n";
                    }
                }

                auto &territoriosGrafo = juego.getGame().getGrafo().getvertices();
                int choose = -1;
                int i = 0;
                for (auto tGrafo: territoriosGrafo) {
                    if (tGrafo.getIdTerritorio() == optionTerr) {
                        choose = i;
                        break;
                    }
                    i++;
                }

                auto vecinosSelected = juego.getGame().getGrafo().sucesores(choose);

                cout << "Seleccione el vecino el cual quiere atacar: ";
                set<int> validVertex;
                for (auto v: vecinosSelected) {
                    auto itTerr = territoriosGrafo.begin();
                    advance(itTerr, v);
                    validVertex.insert(v);
                    cout << v << " -> " << itTerr->getNombre() << " con un costo " << juego.getGame().getGrafo().CostoArco(choose, v) << endl;
                }
                int chooseVertex = -1;

                while (!validVertex.count(chooseVertex)) {
                    cin >> chooseVertex;

                    if (!validVertex.count(chooseVertex)) {
                        cout << "Ups, ese vecino no existe\n";
                    }
                }

                // Atacante lanza 3 dados de color rojo
                // Defiende 2 de blanco
                // Si el atacante > defensor  -> defensor pierde una tropa
                // Si el atacante < defensor  -> atacante pierde una tropa
                // Si atacante == defensor -> atacante pierde una tropa
                int numTropasAtacante = 1000000, numTropasDefensor = 1000000;

                while (numTropasAtacante > 0 && numTropasDefensor > 0) {
                    auto dadosAtacante = juego.getGame().tirarDados(3);
                    auto dadosDefensor = juego.getGame().tirarDados(2);

                    dadosAtacante.sort();

                    int sumAtacante = 0, sumDefensor=0;
                    auto resultAtacante = dadosAtacante.end();
                    resultAtacante--;
                    sumAtacante += *resultAtacante;
                    resultAtacante--;
                    sumAtacante += *resultAtacante;


                    resultAtacante = dadosDefensor.begin();
                    sumDefensor += *resultAtacante;
                    resultAtacante++;
                    sumDefensor += *resultAtacante;

                    auto itTerritorioGrafo = territoriosGrafo.begin();

                    if (sumAtacante > sumDefensor) {
                        advance(itTerritorioGrafo, chooseVertex);
                        itTerritorioGrafo->setTropas(itTerritorioGrafo->getTropas()-1);
                    } else if (sumAtacante < sumDefensor) {
                        advance(itTerritorioGrafo, choose);
                        itTerritorioGrafo->setTropas(itTerritorioGrafo->getTropas()-1);
                    } else {
                        advance(itTerritorioGrafo, choose);
                        itTerritorioGrafo->setTropas(itTerritorioGrafo->getTropas()-1);
                    }

                    itTerritorioGrafo = territoriosGrafo.begin();
                    advance(itTerritorioGrafo, choose);
                    numTropasAtacante = itTerritorioGrafo->getTropas();

                    itTerritorioGrafo = territoriosGrafo.begin();
                    advance(itTerritorioGrafo, chooseVertex);
                    numTropasDefensor = itTerritorioGrafo->getTropas();
                }

                int fortificar = 0;
                cout << "Fortificar territorio?: "; cin >> fortificar;

                if (fortificar) {
                    cout << "Seleccione cuales territorios quiere fortificar y la cantidad de tropas: \n";
                    cout << "El formato es: [from to tropas]: ";

                    for (auto terr : juego.getGame().getTurno()->getTerritorios()) {
                        cout << terr.getIdTerritorio() << " -> " << terr.getNombre() << " con tropas " << terr.getTropas() << endl;
                    }
                    string from, to;
                    int tropas;
                    cin >> from >> to >> tropas;

                    int j = 0;
                    Territorio fromT, toT;
                    for (auto &terr : juego.getGame().getTurno()->getTerritorios()) {
                        if (terr.getIdTerritorio() == from) {
                            fromT = terr;
                        }
                    }
                    list<Territorio>::iterator fromI, toI;
                    bool readyFrom = false, readyTo = false;
                    for (
                            auto itG = juego.getGame().getTurno()->getTerritorios().begin();
                            itG != juego.getGame().getTurno()->getTerritorios().end();
                            itG++
                            ) {
                        if (itG->getIdTerritorio() == from) {
                            fromI = itG;
                            auto nuevo = juego.getGame().getTurno()->getTerritorios().begin();
                            itG = nuevo;
                            readyFrom = true;
                        }

                        if (itG->getIdTerritorio() == to) {
                            toI = itG;
                            auto nuevo = juego.getGame().getTurno()->getTerritorios().begin();
                            itG = nuevo;
                            readyTo = true;
                        }

                        if (readyFrom && readyTo) break;
                    }
                    juego.getGame().fortificarTerritorio(*fromI, *toI, tropas);


                }

                break;
            }

            case guardar: {

                auto file = command.begin();
                file++;
                cout << *file << endl;
                if ( !saveGame.guardarPartida(juego.getGame(), *file) ) {
                    cout << "Ocurrion algo con el guardado de la partida normal\n";
                }

                break;
            }

            case guardar_comprimido : {

                auto itCommand = command.begin();
                itCommand++;

                string fileCompress = saveGame.encode(*itCommand);

                if (fileCompress == "\0") {
                    cout << "Algo ha salido mal con el archivo comprimido\n";
                    break;
                }

                cout << "Se ha guardado el archivo con el nombre: " << fileCompress << endl;

                break;
            }

            case inicializar_comprimido: {

                auto it = command.begin();
                it++;

                cout << "Se ha escrito el archivo en " << saveGame.decode(*it) << endl;

                break;
            }

            default:
                break;
        }
    } while (*it != "salir");
    return 0;
}
