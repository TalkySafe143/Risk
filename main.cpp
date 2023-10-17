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
