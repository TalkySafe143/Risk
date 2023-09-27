#include <iostream>
#include "TADS/Territorio.h"
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
        char* str;
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
            case inicializar:
                cout << "Inicializar\n";
                system("ascii-image-converter continentes.png -f -b --dither -C");
                cout << "Ingrese su continente: ";
                int a;
                cin >> a;
                break;
            case turno:
                cout << "turno\n";
                break;
            default:
                break;
        }
    } while (*it != "salir");

    return 0;
}
