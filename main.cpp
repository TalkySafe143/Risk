#include <bits/stdc++.h>
#include "TADS/Interfaces.h"

using namespace std;

enum StringOptions {
    inicializar,
    turno,
    invalido
};

StringOptions evalString(string a) {
    if (a == "inicializar") return inicializar;
    else if (a == "turno") return turno;
    else return invalido;
}

int main() {
    system("ascii-image-converter title.png -f -b --dither -C");
    list<string> command;
    list<string>::iterator it;
    // inicializar
    Interfaces juego;                   //creo el juego
    bool juegoIniciado = false;
    bool primerTurno = false;
    bool juegoFinalizado = false;
    do {
        cout << "Ingrese su comando: ";
        command.clear();
        char* str = new char[100];
        cin.getline(str, 50);

        char *p = strtok(str, " ");
        if (p != nullptr) {
            while (p != nullptr){
                command.emplace_back(p);
                p = strtok(nullptr, " ");
            }
        } else {
            command.emplace_back(str);
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
                break;
            }
            case turno: {                      //turno <id_jugador>
                if ()
                break;
            }
            default:
                break;
        }
    } while (*it != "salir");
    return 0;
}
