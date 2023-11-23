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
    inicializar_comprimido,
    conquista_mas_barata
};

StringOptions evalString(string a) {
    if (a == "inicializar") return inicializar;
    else if (a == "turno") return turno;
    else if (a == "guardar") return guardar;
    else if (a == "guardar_comprimido") return guardar_comprimido;
    else if (a == "inicializar_comprimido") return inicializar_comprimido;
    else if (a == "conquista_mas_barata") return conquista_mas_barata;
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

                    if (initOption == 1) {  //inicializar con archivo
                        string fileName;
                        cout << "Escriba el nombre del archivo para inicializar el juego: ";
                        cin >> fileName;
                        juego.getGame().iniciarJuego(
                                *juego.getGame().inicializarJugadores(fileName)
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

                if (juegoFinalizado) {
                    cout << "Esta partida ya tuvo un ganador.\n";
                    break;
                }
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
                    break;
                }

                primerTurno = false;

                int numberCont = juego.efectuarTurno();
                if (numberCont == 6) {
                    cout << "Ganaste el juego " << juego.getGame().getTurno()->getNombre() << ". Felicidades.\n";
                    juegoFinalizado = true;
                }

                break;
            }

            case guardar: {

                auto file = command.begin();
                file++;
                if ( !saveGame.guardarPartida(juego.getGame(), *file) ) {
                    cout << "Ocurrio algo con el guardado de la partida normal\n";
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

                cout << "Se ha escrito el archivo en " << saveGame.decode(*it) << " por favor, ingrese el comando inicializar para indicar la incialización con dicho archivo"  << endl;

                break;
            }

            case conquista_mas_barata: {

                if (juegoFinalizado) {
                    cout << "Esta partida ya tuvo un ganador.\n";
                    break;
                }
                list<Territorio> grafoLista = juego.getGame().getGrafo().getvertices();
                Grafo<Territorio> grafo = juego.getGame().getGrafo();
                list<Territorio> territorios = juego.getGame().getTurno()->getTerritorios();
                unsigned long long n = grafoLista.size();
                queue<int> pos ; //la posicion del territorio del jugador en la lista del grafo

                for(Territorio tJugador : territorios){
                    for(int i=0; i<n; i++){
                        if(tJugador == grafo.InfoVertice(i)){
                            pos.push(i);
                        }
                    }
                }

                //llamo el dijkstra para todos los territorios del jugador
                int c=0; int costoMin=0;
                for(int i=0; i<pos.size(); i++){
                    juego.getGame().conquistaMasBarata(juego.getGame().getGrafo(), pos.front(), c);
                    if(c < costoMin){
                        costoMin = c;
                    }
                    pos.pop();
                }
                cout<<"Para la conquista más barata debe conquistar " << costoMin<<" unidades de ejercito";
            }

            default:
                break;
        }
    } while (*it != "salir");
    return 0;
}
