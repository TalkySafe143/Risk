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
    Interfaces ui;
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
                ui.inicializarJuego();
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
    return 0;
}
