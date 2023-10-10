#include <iostream>
#include "TADS/Territorio.h"
#include "TADS/Jugador.h"
#include "TADS/ArbBin.h"
#include "TADS/nodoB.h"

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
                cout << "Inicializar\n";
                system("ascii-image-converter continentes.png -f -b --dither -C");
                int CantJugadores;
                cout << "Ingresa la cantidad de jugadores con el que quieres iniciar el juego" << endl;
                cout << "Recuerda que minimo puedes jugar con 2 y maximo 6" << endl;
                cin >> CantJugadores;

                if ((CantJugadores < 2) || (CantJugadores > 6)) {
                    cout << "Recuerda la regla minima y maxima de jugadores" << endl;
                    return CantJugadores;
                } else if ((CantJugadores > 2) || (CantJugadores < 6)) {
                    cout << "Su cantidad de jugadores es:" << CantJugadores;

                }

                int InfanteriasPorJugador = 0;

                if (CantJugadores == 3) {
                    InfanteriasPorJugador = 35;
                } else if (CantJugadores == 4) {
                    InfanteriasPorJugador = 30;
                } else if (CantJugadores == 5) {
                    InfanteriasPorJugador = 25;
                } else if (CantJugadores == 6) {
                    InfanteriasPorJugador = 20;
                } else {
                    std::cout << "Número de jugadores no válido." << std::endl;
                    return 1;
                }
                //generamos valores aleatorios para el valor de tirada
                std::srand(static_cast<unsigned int>(std::time(nullptr)));
                //en esta lista guardo los jugadores con su nombre y  cantidad de infanterias
                std::list<Jugador> jugadores;

                for (unsigned int i = 0; i < CantJugadores; i++) {
                    cout << "Ingresame los nombres de los jugadores: ";
                    string nombre;
                    cin >> nombre;
                    //Jugador jugador(nombre, InfanteriasPorJugador, InfanteriasPorJugador);

                    //jugadores.push_back(jugador);
                }

                jugadores.sort([](const Jugador &a, const Jugador &b) {
                    return a.getNombre() < b.getNombre(); // Ordenar en orden ascendente
                });

                std::cout << "Lista de jugadores y cantidad de infanterías asignadas:" << std::endl;
                for (const Jugador &jugador: jugadores) {
                    //std::cout << "Nombre: " << jugador.getNombre() << ", Infanterías: " << jugador.getInfanterias()
                             // << std::endl;
                }
                break;
            }
            case turno: {
                cout << "turno\n";
                break;
            }
            default:
                break;
        }
    } while (*it != "salir");
    // Este es un cambio para la rama tarjetas
    return 0;
}
