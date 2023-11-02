//
// Created by talkysafe143 on 1/10/23.
//

#include "Interfaces.h"

Risk &Interfaces::getGame(){
    return game;
}

void Interfaces::setGame(const Risk &game) {
    Interfaces::game = game;
}

void Interfaces::inicializarJuego() {
    //system("ascii-image-converter continentes.png -f -b --dither -C");
    int CantJugadores;
    cout << "Ingresa la cantidad de jugadores con el que quieres iniciar el juego" << endl;
    cout << "Recuerda que minimo puedes jugar con 2 y maximo 6" << endl;
    cin >> CantJugadores;

    if ((CantJugadores < 2) || (CantJugadores > 6)) {
        cout << "Recuerda la regla minima y maxima de jugadores" << endl;
        return;
    } else if ((CantJugadores > 2) || (CantJugadores < 6)) {
        cout << "Su cantidad de jugadores es:" << CantJugadores;
    }


    set<string> coloresSeleccionados;
    list<Jugador> jugadores;
    for (int i = 0; i < CantJugadores; i++) {
        Jugador jugador;
        string nombre, color;
        cout << endl;
        cout << "Ingrese el nombre del jugador: " << i+1 << ": ";
        cin >> nombre; jugador.setNombre(nombre);
        bool validColor = false;
        while (!validColor) {
            cout << "Ingrese el color del jugador " << i+1 << ": ";
            cin >> color;
            if (coloresSeleccionados.count(color)) {
                cout << "Este color ya ha sido seleccionado\n";
                system("pause");
                system("cls");
                continue;
            }

            coloresSeleccionados.insert(color);
            validColor = true;
            jugador.setColor(color);
        }

        int tropasRestantes;

        switch (CantJugadores) {
            case 2: {
                tropasRestantes = 40;
                break;
            };
            case 3: {
                tropasRestantes = 35;
                break;
            };
            case 4: {
                tropasRestantes = 30;
                break;
            };
            case 5: {
                tropasRestantes = 25;
                break;
            };
            case 6: {
                tropasRestantes = 20;
                break;
            }
        }

        while (tropasRestantes > 0) {
            int tropasSeleccionadas;
            cout << "Tiene " << tropasRestantes << " tropas restantes para ubicar\n";
            cout << "¿Cuantas tropas desea ubicar a un territorio?: ";
            cin >> tropasSeleccionadas;

            if (tropasSeleccionadas > tropasRestantes) {
                cout << "No puede elegir mas tropas que las que tiene disponible\n";
                system("pause");
                system("cls");
                continue;
            }
            Interfaces::asignarTropasTerritorio(tropasSeleccionadas, jugador);
            tropasRestantes -= tropasSeleccionadas;
        }

        jugadores.push_back(jugador);
    }

    Interfaces::game.setJugadores(jugadores);

    Interfaces::game.iniciarJuego(Interfaces::game.getJugadores());
}

void Interfaces::asignarTropasTerritorio(int tropas, Jugador &jugador) {
    list<Continente> continentes = Interfaces::game.getContinentes();

    set<string> territoriosLeft;
    bool valid = false;

    while (!valid) {
        cout << "Territorios\n";
        for (auto &continente: continentes) {
            for (auto &territorio: continente.getTerritorios()) {
                if (territorio.getTropas() == 0) {
                    territoriosLeft.insert(territorio.getIdTerritorio());
                    cout << "ID: " << territorio.getIdTerritorio() << " -> " << territorio.getNombre() << endl;
                }
            }
        }

        string idTerritorio;
        cout << "Elige el ID de un territorio para ubicar tus tropas: ";
        cin >> idTerritorio;

        if (!territoriosLeft.count(idTerritorio))  {
            cout << "El ID que escogio no existe\n";
            system("pause");
            system("cls");
            continue;
        }
        for (auto continente: continentes) {
            for (auto territorio: continente.getTerritorios()) {
                if (idTerritorio == territorio.getIdTerritorio()) {
                    territorio.setTropas(tropas);
                    jugador.agregarTerritorio(territorio);
                    valid = true;
                    break;
                }
            }
        }
    }

    cout << "Se han asignado " << tropas << " a el territorio seleccionado\n";
}
