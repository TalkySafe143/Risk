//
// Created by talkysafe143 on 1/10/23.
//

#include "Huffman.h"
#include "ArbBin.cpp"
#include "nodoB.cpp"
#include "Jugador.h"
#include <iostream>
#include <fstream>

bool cmp(ArbBin<FreqChar>* a, ArbBin<FreqChar>* b) {
    return a->GetInfo() < b->GetInfo();
}

/**
 * Ahí agregué la funcion en el .h, pero toca que tenga cuidado cuando escriba las cartas
 * Acuerdese que las cartas es por cada jugador en la partida, no de todo el juego
 * Toca que verifique si se esta escribiendo bien el archivo
 * 
 * Toca que le meta turbo a implementar eso porque esta parte de manejo de bits es un visag
 * Busque si algo #pragma push(1) y pille lo que hace, las estructuras y eso porque eso es un camello
 * Le recomiendo implementar esto a mas tardar el fincho ñero, porque toca comenzar a probar y 
 * mirar errores, si todo funciona bien y corregir, le recomiendo):
*/
int Huffman::guardarPartida(Risk game, string file) {

    std::ofstream archivo(file);

    if (!archivo.is_open()) {
        return -1;
    }

     std::list<Jugador>& jugadores = game.getJugadores();
     std::list<Continente>& continentes = game.getContinentes();
     std::list<Carta>& cartas = game.getCartas();
     std::list<Jugador>::iterator& turno = game.getTurno();

    archivo << jugadores.size() << std::endl;

    for (auto& jugador : jugadores) {
        archivo << jugador.getNombre() << ";" << jugador.getColor() << ";";

        const std::list<Territorio> territorios = jugador.getTerritorios();
        archivo << territorios.size() << ";";
        for (auto territorio : territorios) {
            archivo << territorio.getIdTerritorio() << ";" << territorio.getTropas() << ";";
        }

        const std::list<Carta>& cartasJugador = jugador.getCartas();
        archivo << cartasJugador.size() << ";";
        for (auto carta : cartasJugador) {
            archivo << carta.getId() << ";";
        }

        archivo << std::endl;
    }

    archivo.close();
    return 1;
}

/**
 * Esta funcion tiene como proposito contruir el arbol de Huffman
 * @param freq La frecuencia de los caracteres del archivo de configuracion
 */
void Huffman::construirArbol(map<char, int> freq) {
    deque<ArbBin<FreqChar>*> pq;

    for (auto [c, value]: freq) {
        pq.push_back(new ArbBin<FreqChar>({ c, value }));
    }

    sort(pq.begin(), pq.end(), cmp);

    while (pq.size() > 1) {
        ArbBin<FreqChar>* left = *(pq.begin());
        pq.erase(pq.begin());
        ArbBin<FreqChar>* right = *(pq.begin());
        pq.erase(pq.begin());

        FreqChar mergedFreqChar{'#', left->GetInfo().freq + right->GetInfo().freq};
        ArbBin<FreqChar>* mergedNode = new ArbBin<FreqChar>(mergedFreqChar);
        bool ok;
        mergedNode->CuelgaSubarbolIzq(*left, ok);
        mergedNode->CuelgaSubarbolDer(*right, ok);
        pq.push_back(mergedNode);
    }

    if (!pq.empty()) {
        ArbBin<FreqChar>* topNode = *(pq.begin());

        ArbBin<FreqChar>* left = topNode->GetIzqArbBin();
        ArbBin<FreqChar>* der = topNode->GetDerArbBin();
        tree = new ArbBin<FreqChar>(topNode->GetInfo());
        bool ok;
        tree->CuelgaSubarbolIzq(*left, ok);
        tree->CuelgaSubarbolDer(*der, ok);
    }
}



string Huffman::obtenerCodigoHuffman(char c, ArbBin<FreqChar>* tree, string curr) {
    if (tree->IsEmpty()) {
        return curr+'2';
    }

    if (tree->GetInfo().c == c) {
        return curr;
    }

    string l = obtenerCodigoHuffman(c, tree->GetIzqArbBin(), curr + '0');
    string d = obtenerCodigoHuffman(c, tree->GetDerArbBin(), curr + '1');

    if (l[l.size()-1] != '2') {
        return l;
    }

    if (d[d.size()-1] != '2') {
        return d;
    }

    return curr + '2';
}


/**
 * Esta funcion tiene como proposito decodificar un archivo binario y escribir un archivo de texto
 * con la decodificacion
 * @param file El nombre del archivo binario
 * @return El nombre del archivo de texto escrito ("\0" si se produjo un error)
 * LA CLASE QUE LLAME A ESTE METODO TIENE LA RESPONSABILIDAD DE BORRAR EL ARCHIVO DE TEXTO
 */
string Huffman::decode(string file) {
    // Abrir el archivo binario en modo lectura
    ifstream inputFile(file, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo binario." << endl;
        return "\0"; // Devolver una cadena nula para indicar un error
    }

    // Leer n (cantidad de caracteres diferentes)
    short numDistinctChars;
    inputFile.read(reinterpret_cast<char*>(&numDistinctChars), sizeof(short));

    // Leer ci y fi para cada carácter y construir el mapa de frecuencias
    map<char, int> freq;
    for (short i = 0; i < numDistinctChars; ++i) {
        char c;
        int charFreq;
        inputFile.read(&c, sizeof(char));
        inputFile.read(reinterpret_cast<char*>(&charFreq), sizeof(long long));
        freq[c] = charFreq;
    }

    // Leer w (longitud original del archivo)
    int originalLength;
    inputFile.read(reinterpret_cast<char*>(&originalLength), sizeof(long long));

    // Construir el árbol de Huffman basado en las frecuencias
    construirArbol(freq);

    // Decodificar el contenido del archivo binario
    string bitBuffer;
    char byte;
    while (inputFile.read(&byte, sizeof(char))) {
        // Convertir el byte a una cadena de bits de 8 bits
        bitset<8> bits(byte);
        string bitString = bits.to_string();
        
        // Agregar los bits al búfer de bits
        bitBuffer += bitString;

    }

    inputFile.close();

    string decodedString = "";
    reverse(bitBuffer.begin(), bitBuffer.end());
    while (decodedString.size() < originalLength) {
        decodedString += extractChar(bitBuffer, this->tree);
    }

    // Verificar la longitud del texto decodificado
    if (decodedString.size() != static_cast<size_t>(originalLength)) {
        cerr << "Error: Longitud del texto decodificado no coincide con la longitud original." << endl;
        return "\0"; // Devolver una cadena nula para indicar un error
    }

    // Escribir el texto decodificado en un archivo de texto
    ofstream outputFile("decoded.txt");
    if (!outputFile.is_open()) {
        cerr << "Error al abrir el archivo de texto para escribir la decodificación." << endl;
        return "\0"; // Devolver una cadena nula para indicar un error
    }

    outputFile << decodedString;
    outputFile.close();

    // Devolver el nombre del archivo de texto creado
    return "decoded.txt";

}


/**
 * Esta funcion tiene como proposito codificar un archivo de texto y escribir un archivo binario
 * con la codificacion de dicho archivo
 * @param file El nombre del archivo de texto
 * @return El nombre del archivo binario escrito ("\0" si se produjo un error)
 * LA CLASE QUE LLAME A ESTE METODO TIENE LA RESPONSABILIDAD DE BORRAR EL ARCHIVO DE TEXTO
 */
string Huffman::encode(string file) {
    
    ifstream inputFile(file);
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo de texto." << endl;
        return "\0"; 
    }

    string textContent((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    map<char, int> freq;
    for (char c : textContent) {
        freq[c]++;
    }

    construirArbol(freq);

    string encodedText;
    for (char c : textContent) {

        string huffmanCode = obtenerCodigoHuffman(c, tree, "");
        encodedText += huffmanCode;
    }

    int numDistinctChars = freq.size();

    ofstream outputFile("encoded.bin", ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error al abrir el archivo binario para escribir la codificación." << endl;
        return "\0";
    }

    outputFile.write(reinterpret_cast<char*>(&numDistinctChars), sizeof(short));

    for (const auto& pair : freq) {
        char c = pair.first;
        int freq = pair.second;
        outputFile.write(&c, sizeof(char));
        outputFile.write(reinterpret_cast<char*>(&freq), sizeof(long long));
    }

    int originalLength = textContent.size();
 
    outputFile.write(reinterpret_cast<char*>(&originalLength), sizeof(long long));

    for (size_t i = 0; i < encodedText.size(); i += 8) {
        string byte = encodedText.substr(i, 8);
        
        while (byte.size() < 8) {
            byte += '0';
        }
        bitset<8> bits(byte);
        char byteValue = static_cast<char>(bits.to_ulong());
        outputFile.write(&byteValue, sizeof(char));
    }
    outputFile.close();

    return "encoded.bin";
}

char Huffman::extractChar(string &buffer, ArbBin<FreqChar>* tree) {
    if (tree->IsEmpty()) return '\0';

    if (tree->GetDerArbBin()->IsEmpty() && tree->GetIzqArbBin()->IsEmpty()) {
        return tree->GetInfo().c;
    }

    char search = buffer[buffer.size()-1];
    buffer.pop_back();
    if (search == '1') {
       return extractChar(buffer, tree->GetDerArbBin());
    } else {
        return extractChar(buffer, tree->GetIzqArbBin());
    }
}