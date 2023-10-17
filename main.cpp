#include <iostream>
#include "TADS/Territorio.h"
#include "TADS/Jugador.h"
#include "TADS/ArbBin.h"
#include "TADS/nodoB.h"
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
    cout << "Ingrese su comando: ";
    list<string> command;
    list<string>::iterator it;

    // inicializar
    Interfaces juego;
    bool juegoIniciado = false;
    bool juegoFinalizado = false;

    do { // Segmentation fault
        command.clear();
        char* str = new char[100];
        cin.getline(str, 50);
        cout << "Antes del switch\n";
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
                    juego.inicializarJuego();
                    juegoIniciado = true;
                    cout << "(Inicialización satisfactoria) El juego se ha inicializado correctamente." << endl;
                }else{
                    cout << "(Juego en curso) El juego ya ha sido inicializado." << endl;
                }
                break;
            }
            case turno: {                   //turno <id_jugador>
                if (!juegoIniciado) {cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente.\n"; break;}
                if (juegoFinalizado) {cout << "(Juego terminado) Esta partida ya tuvo un ganador.\n";break;}

                string playerIdInput = *it++;                            //id que me dan  <id_jugador>

                //mirar si el jugador está en el juego
                bool esta = false;
                list<Jugador> jugadores = juego.getGame().getJugadores();
                for(auto z : jugadores){
                    if(z.getId() == playerIdInput) esta = true;
                }
                if(!esta) {cout<<"(Jugador no válido) El jugador <id_jugador> no forma parte de esta partida.\n"; break;}

                //mirar si es el turno del jugador que me dan
                string playerId = juego.getGame().getTurno()->getId();   //id del jugador que le toca
                if (playerIdInput != playerId){ cout << "(Jugador fuera de turno) No es el turno del jugador <id_jugador>\n"; break;}


                //hace lo del turno

                // mira si ya gano (ej: conquistó todos los territorios)
                if (//el jugador ganó) {
                    juegoFinalizado = true;
                    cout << "(Juego terminado) El jugador " << playerId << " ha ganado." << endl;
                } else {
                    cout << "(Turno terminado correctamente) El turno del jugador " << playerId << " ha terminado."
                         << endl;
                }



                break;
            }
            default:
                break;
        }
    } while (*it != "salir");
    // Este es un cambio para la rama tarjetas
    return 0;
}
