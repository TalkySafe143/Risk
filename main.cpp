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
    Interfaces juego;                   //creo el juego
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
            case turno: {                      //turno <id_jugador>
                if (!juegoIniciado) {cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente.\n"; break;}
                if (juegoFinalizado) {cout << "(Juego terminado) Esta partida ya tuvo un ganador.\n";break;}

                string playerIdInput = *it++;  //id que me dan  <id_jugador>

                //mirar si el jugador está en el juego
                bool esta = false;
                list<Jugador> jugadores = juego.getGame().getJugadores();          //____los jugadores del juego____
                for(auto z : jugadores){
                    if(z.getId() == playerIdInput) esta = true;  //recorro t.odo el juego por jugador que entre
                }
                if(!esta){cout<<"(Jugador no válido) El jugador" << playerIdInput << "no forma parte de esta partida.\n"; break;}

                Jugador jug = juego.getGame().avanzarTurno(1); //el jugador del turno que toca

                if(jug.getId() != playerIdInput){
                    juego.getGame().avanzarTurno(-1);
                    cout<<"(Jugador fuera de turno) No es el turno del jugador" << playerIdInput << "\n";
                }


                //hace lo del turno

                ///Obtener y ubicar nuevas unidades de ejército
                //Territorios   ---unidades adicionales
                list<Territorio> territorios = jugador.getTerritorios();
                int noTerritorios = territorios.size();
                int unidadesAdicionales = noTerritorios/3;//cantidad de unidades adicionales que puede reclamar
                cout<<"usted puede reclamar : "<<unidadesAdicionales;



                //Continentes    ---unidades adicionales
                //si ocupa todos los rerritorios de un continente asigna un #ro de tropas
                //-pero no hay nada que asocie continenetes con territotios-osea tantos territorios van en tal continente-
                switch (idContinente) {
                    case "america del sur" || "australia":
                        jugador. //donde puts están las tropas? -> territorio
                    case:

                    case:
                }

                //Cartas         ---unidades adicionales
                list<Carta> cartasJugador= jugador.getCartas();
                if(cartasJugador.size() == 3){
                    //cómo se que las cartas tienen el miso
                }

                cout<<"cuáles de sus territorios las quiere asignar y en qué cantidad\n";
                cout<<"territorios : ";
                for(auto t : territorios){
                    cout<<t.getNombre()<<endl; //imprime los territorios
                }

                ///Atacar un territorio vecino
                //preguntar la configuracion del ataque:
                string deDonde, aDonde;
                cout<<"De que territorio ataca"; cin>>deDonde;
                cout<<"A que territorio ataca"; cin>>aDonde;

                //  ----verificar condicones descritas---- grafos?  -> sieñor


                //Luego debería informar los valores obtenidos con los dados, y la cantidad de unidades que se ganan o
                //pierden

                juego.getGame().tirarDados();

                ///Fortificar la posición.



                // mira si ya gano (ej: conquistó todos los territorios)
                //opciones pa ganar
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
