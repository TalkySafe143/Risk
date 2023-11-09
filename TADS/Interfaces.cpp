//
// Created by talkysafe143 on 1/10/23.
//

#include "Interfaces.h"
#include "Grafo.cpp"

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
    list<Jugador> *jugadores = new list<Jugador>;
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
            jugador.setId(to_string(i));
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

        jugadores->push_back(jugador);
    }

    Interfaces::game.setJugadores(*jugadores);

    Interfaces::game.iniciarJuego(Interfaces::game.getJugadores());
}

int Interfaces::asignarTropasTerritorio(int tropas, Jugador &jugador) {
    list<Continente> &continentes = Interfaces::game.getContinentes();

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
        for (auto &continente: continentes) {
            for (auto &territorio: continente.getTerritorios()) {
                if (idTerritorio == territorio.getIdTerritorio()) {
                    territorio.setTropas(tropas);


                    auto &vertexs = Interfaces::game.getGrafo().getVerticesNode();
                    int u = 0;
                    for (auto &someTerr: vertexs) {
                        if (territorio == someTerr.getData()) {
                            someTerr.getData().setTropas(tropas);
                            break;
                        }
                        u++;
                    }

                    auto neighboors = Interfaces::game.getGrafo().sucesores(u);

                    for (int v: neighboors) {
                        Interfaces::game.getGrafo().changeArcCost(v, u, tropas);
                    }

                    jugador.agregarTerritorio(territorio);
                    valid = true;
                    break;
                }
            }
        }
    }

    cout << "Se han asignado " << tropas << " a el territorio seleccionado\n";

    return tropas;
}

int Interfaces::efectuarTurno() {
        cout << "------- Obteniendo nuevas unidades de ejercito -------\n";

        // Mira las tropas que le corresponde por los territorios y los continentes
        int numTropas = Interfaces::game.reasignarTropas();

        // Cuando tenga 3 cartas se intercambian por tropas
        numTropas += Interfaces::game.intercambiarCartas();

        if (numTropas > 0) Interfaces::asignarTropasTerritorio(numTropas, *game.getTurno());

        // Coge la lista de territorios del atacante
        auto &territoriosAtacantes = Interfaces::game.getTurno()->getTerritorios();

        // Recuperamos el grafo del juego
        auto &grafoGame = Interfaces::game.getGrafo();

        // Se hace un set para ingresar los IDs/Opciones validas
        set<string>validFields;

        attack:
        cout << "------- Atacando territorios -------\n";
        cout << "Seleccione un territorio desde el cual quiera atacar. \n";
        for (auto terr: territoriosAtacantes) {
            cout << terr.getIdTerritorio() << " -> " << terr.getNombre() << endl;
            validFields.insert(terr.getIdTerritorio());
        }
        string idFieldfrom = "";

        // set.count() cuenta cuantas veces hay un string en el set, si no está entonces retorna 0
        // Si la opcion que ingrese el usuario no esta dentro del set, quiere decir que es un territorio invalido
        // Si el ID no esta en el set, quiere decir que el jugador NO tiene ese territorio
        while (!validFields.count(idFieldfrom)) {
            cout << "Escriba el ID del territorio: ";
            cin >> idFieldfrom;
        }

        int from, i = 0, to=-1;

        // Aqui se obtiene la posicion del vertice en el grafo del territorio seleccionado
        for (auto terr: grafoGame.getVerticesNode()) {
            if (terr.getData().getIdTerritorio() == idFieldfrom) {
                from = i;
                break;
            }
            i++;
        }

        // Se limpia el set (Elimina los elementos que tenga) para volver a utilizarlo
        validFields.clear();
        cout << "¿A que territorio quiere atacar?\n";
        int validNeigh = 0;

        // Se recuperan los territorios adyancentes de forma de vertices del grafo
        for (auto vertex: grafoGame.sucesores(from)) {
            int j = 0;
            bool valid = true;

            // Como los vertices se toman como las posiciones de la lista de vertices, se busca por la lista de vertices
            for (auto terGraph: grafoGame.getVerticesNode()) {
                // Para evitar hacerlo con iteradores se utiliza el for
                if (j == vertex) {
                    // Cuando encuentra el vertice que estamos buscando del grafo
                    for (auto fromTerr: territoriosAtacantes) {
                        // Se verifica si el jugador ya tiene ese territorio
                        if (fromTerr.getIdTerritorio() == terGraph.getData().getIdTerritorio()) {
                            valid = false; // En caso de que el jugador ya tenga el territorio, se indica como que no es valido
                            break;
                        }
                    }

                    if (!valid) break;

                    validNeigh++;
                    // Imprime los territorios adyacentes
                    validFields.insert(terGraph.getData().getIdTerritorio());
                    cout << terGraph.getData().getIdTerritorio() << " -> " << terGraph.getData().getNombre() << endl;
                    break;
                }
                j++;
            }
        }

        if (!validNeigh) {
            cout << "Ups, todos los territorios adyacentes son controladeos por ti.\n";
            goto attack;
        }

        string idFieldTo="";

        // COn el mismo mecanismo del set, se pide la opcion de que territorio adyacente desea atacar
        while (!validFields.count(idFieldTo)) {
            cout << "Seleccione que territorio quiere atacar: ";
            cin >> idFieldTo;
        }


        // Este for tiene como objetivo obtener la posicion del vertice de la opcion que se escogió
    for (auto vertex: grafoGame.sucesores(from)) {
        int j = 0;
        bool valid = true;
        for (auto terGraph: grafoGame.getVerticesNode()) {
            if (j == vertex) {
                for (auto fromTerr: territoriosAtacantes) {
                    if (idFieldTo == terGraph.getData().getIdTerritorio()) {
                        to = vertex;
                        break;
                    }
                }
                break;
            }
            j++;
        }
        if (to != -1) break;
    }


    // En esta parte se toman las referencias del NODO del grafo al que corresponden el territorio atacante y el defensor
    auto nodoGraph = grafoGame.getVerticesNode().begin();

    // Por medio del advance y de la posicion del vertice, se puede obtener el nodo de la lista
    advance(nodoGraph, from);
    auto &fromGraphTerr = *nodoGraph;
    nodoGraph = grafoGame.getVerticesNode().begin();
    advance(nodoGraph, to);
    auto &toGraphTerr = *nodoGraph;

    cout << "------- ¡Hora de tirar los dados! -------\n";
    int optionContinue = -1;

    // Va a tirar los dados mientras algunos de los dos territorios tengan tropas y se desee continuar
    while (fromGraphTerr.getData().getTropas() > 0 && toGraphTerr.getData().getTropas() > 0 && optionContinue != 0) {

        auto dadosAtacante = game.tirarDados(3);
        auto dadosDefensor = game.tirarDados(2);

        dadosAtacante.sort();

        int sumAtacante =0, sumDefensor =0;

        auto itDados = dadosAtacante.end(); itDados--;
        sumAtacante += *itDados; itDados--;
        sumAtacante += *itDados;

        itDados = dadosDefensor.end(); itDados--;
        sumDefensor += *itDados; itDados--;
        sumAtacante += *itDados;

        if (sumAtacante > sumDefensor) {
            cout << "EL atacante gano la tirada de los dados.\n";
            toGraphTerr.getData().setTropas(toGraphTerr.getData().getTropas()-1);
        } else if (sumAtacante < sumDefensor) {
            cout << "EL defensor gano la tirada de los dados.\n";
            fromGraphTerr.getData().setTropas(fromGraphTerr.getData().getTropas()-1);
        } else {
            cout << "EL defensor gano la tirada de los dados.\n";
            fromGraphTerr.getData().setTropas(fromGraphTerr.getData().getTropas()-1);
        }

        cout << "¿Deseas tirar los dados? [1 -> YES / 0 -> NO]: ";
        cin >> optionContinue;
    }

    if (toGraphTerr.getData().getTropas() == 0) {
        int tropasT;
        cout << "¡Conquistaste el territorio el territorio! \n¿Cuantas tropas quieres mover para alla?\n";
        cout << "Tropas disponibles: " << fromGraphTerr.getData().getTropas() << ": ";
        cin >> tropasT;
        toGraphTerr.getData().setTropas(tropasT);

        // Quitarle los territorios al otro jugador
        for (auto &jug: game.getJugadores()) {
            auto itDelete = jug.getTerritorios().begin();
            for (auto &terrJug: jug.getTerritorios()) {
                if (terrJug.getIdTerritorio() == toGraphTerr.getData().getIdTerritorio()) {
                    jug.getTerritorios().erase(itDelete);
                    break;
                }
                itDelete++;
            }
        }

        // Vamos a buscar la carta que corresponde a el territorio que ganamos
        auto cardDelete = Interfaces::game.getCartas().begin();
        for (auto &carta: Interfaces::game.getCartas()) {
            if (carta.getIdTerritorio() == toGraphTerr.getData().getIdTerritorio()) {
                Interfaces::game.getTurno()->agregarCarta(carta);
                break;
            }

            cardDelete++;
        }

        // Quitamos la carta de la mesa
        Interfaces::game.getCartas().erase(cardDelete);

        // Se agregan los territorios y se modifican los valores en el grafo y en el juego
        Interfaces::game.getTurno()->agregarTerritorio(toGraphTerr.getData());
        fromGraphTerr.getData().setTropas(fromGraphTerr.getData().getTropas() - tropasT);
        for (auto &terr: Interfaces::game.getTurno()->getTerritorios()) {
            if (terr == fromGraphTerr.getData()) {
                // Esta comparacion es posible porque a Territorio le sobrecargamos un operador
                terr.setTropas(fromGraphTerr.getData().getTropas());
                break;
            }
        }
    }

    // El atacante perdió
    if (fromGraphTerr.getData().getTropas() == 0) {
        cout << "Lo sentimos, perdiste el territorio):\n";

        for (auto &jug: game.getJugadores()) {
            for (auto &terrJug: jug.getTerritorios()) {
                if (terrJug.getIdTerritorio() == toGraphTerr.getData().getIdTerritorio()) {
                    int tropasT;
                    cout << "Jugador " << jug.getNombre() << " conquistaste el territorio de " << game.getTurno()->getNombre() << "\n¿Cuantas tropas quieres mover para alla?\n";
                    cout << "Tropas disponibles: " << toGraphTerr.getData().getTropas() << ": ";
                    cin >> tropasT;

                    fromGraphTerr.getData().setTropas(tropasT);

                    auto itDelete = Interfaces::game.getTurno()->getTerritorios().begin();
                    for (auto &terr: Interfaces::game.getTurno()->getTerritorios()) {
                        if (terr.getIdTerritorio() == fromGraphTerr.getData().getIdTerritorio()) {
                            Interfaces::game.getTurno()->getTerritorios().erase(itDelete);
                            break;
                        }
                        itDelete++;
                    }
                    jug.agregarTerritorio(fromGraphTerr.getData());
                    toGraphTerr.getData().setTropas(toGraphTerr.getData().getTropas() - tropasT);
                    terrJug.setTropas(toGraphTerr.getData().getTropas());
                }
            }

            // Vamos a buscar la carta que corresponde a el territorio que ganamos
            auto cardDelete = Interfaces::game.getCartas().begin();
            for (auto &carta: Interfaces::game.getCartas()) {
                if (carta.getIdTerritorio() == fromGraphTerr.getData().getIdTerritorio()) {
                    jug.agregarCarta(carta);
                    break;
                }

                cardDelete++;
            }

            // Quitamos la carta de la mesa
            Interfaces::game.getCartas().erase(cardDelete);

        }
    }

    cout << "------- Fortificar territorio -------\n";
    cout << "Determine desde cual territorio quiere extraer sus tropas\n";

    validFields.clear();
    for (auto terr: Interfaces::game.getTurno()->getTerritorios()) {
        cout << terr.getIdTerritorio() << " -> " << terr.getNombre() << " con " << terr.getTropas() << " tropas.\n";
        validFields.insert(terr.getIdTerritorio());
    }
    string idFortificarFrom = "", idFortificarTo ="";
    while (!validFields.count(idFortificarFrom)) {
        cout << "Seleccione el territorio de origen de las tropas: ";
        cin >> idFortificarFrom;
    }
    validFields.erase(idFortificarFrom);

    while (!validFields.count(idFortificarTo)) {
        cout << "Seleccione el territorio de destino de las tropas; ";
        cin >> idFortificarTo;
    }
    int fortificarFrom, fortificarTo;
    i = 0;
    for (auto terr: grafoGame.getVerticesNode()) {
        if (terr.getData().getIdTerritorio() == idFortificarFrom) {
            fortificarFrom = i;
        }

        if (terr.getData().getIdTerritorio() == idFortificarTo) {
            fortificarTo = i;
        }
        i++;
    }
    nodoGraph = grafoGame.getVerticesNode().begin();
    advance(nodoGraph, fortificarFrom);
    auto &nodoFortificarFrom = *nodoGraph;
    nodoGraph = grafoGame.getVerticesNode().begin();
    advance(nodoGraph, fortificarTo);
    auto &nodoFortificarTo = *nodoGraph;
    int tropasRefuerzo;
    cout << "Tropas disponibles para mover: " << nodoFortificarFrom.getData().getTropas() << "\n¿Cuantas desea mover al otro territorio? ";
    cin >> tropasRefuerzo;


    nodoFortificarFrom.getData().setTropas(nodoFortificarFrom.getData().getTropas()-tropasRefuerzo);
    nodoFortificarTo.getData().setTropas(nodoFortificarTo.getData().getTropas()+tropasRefuerzo);

    for (auto &terr: Interfaces::game.getTurno()->getTerritorios()) {
        if (terr == nodoFortificarFrom.getData()) {
            terr.setTropas(nodoFortificarFrom.getData().getTropas());
        }
        if (terr == nodoFortificarTo.getData()) {
            terr.setTropas(nodoFortificarTo.getData().getTropas());
        }

    }

    auto continentesEnPoder = game.getTurno()->verificarContinentes(game.getContinentes());

    int numberCont = 0;
    for (auto jugCont: continentesEnPoder) {
        for (auto gameCont: game.getContinentes()) {
            if (gameCont.getId() == jugCont.getId()) {
                numberCont++;
                break;
            }
        }
    }

    return numberCont;
}
