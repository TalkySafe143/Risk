//
// Created by talkysafe143 on 1/10/23.
//

#include "Huffman.h"
#include "Risk.h"
#include "nodoB.h"
#include "Jugador.h"
#include <iostream>
#include <fstream>


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
int guardarPartida(Risk game, string file) {

    std::ofstream archivo(file);

    if (!archivo.is_open()) {
        std::cout << "La partida no ha sido guardada correctamente." << std::endl;
        return -1;
    }

    // if () {
    //     std::cout << " Esta partida no ha sido inicializada correctamente." << std::endl;
    //     return;
    // }

    const std::list<Jugador>& jugadores = game.getJugadores();
    const std::list<Continente>& continentes = game.getContinentes();
    const std::list<Carta>& cartas = game.getCartas();
    const std::list<Jugador>::iterator& turno = game.getTurno();

    archivo << jugadores.size() << std::endl;
    for (const auto& jugador : jugadores) {
        archivo << jugador.getId() << ";" << jugador.getNombre() << ";" << jugador.getColor() << ";";

        const std::list<Territorio>& territorios = jugador.getTerritorios();
        archivo << territorios.size() << ";";
        for (const auto& territorio : territorios) {
            archivo << territorio.getIdTerritorio() << ";" << territorio.getTropas() << ";";
        }

        const std::list<Carta>& cartasJugador = jugador.getCartas();
        archivo << cartasJugador.size() << ";";
        for (const auto& carta : cartasJugador) {
            archivo << carta.getId() << ";";
        }

        archivo << std::endl;
    }

    archivo.close();
    cout << "La partida ha sido guardada correctamente." << endl;

    return 1;
}

/**
 * Esta funcion tiene como proposito contruir el arbol de Huffman
 * @param freq La frecuencia de los caracteres del archivo de configuracion
 */
void Huffman::construirArbol(map<char, int> freq){

    priority_queue<ArbBin<FreqChar>*, vector<ArbBin<FreqChar>*>, greater<ArbBin<FreqChar>*>> pq;
    bool dummy;
   
    for (const auto& pair : freq) {
        FreqChar freqChar{pair.first, pair.second};
        ArbBin<FreqChar>* arbNodo = new ArbBin<FreqChar>(freqChar);
        pq.push(arbNodo);
    }

   
    while (pq.size() > 1) {
        ArbBin<FreqChar>* left = pq.top();
        pq.pop();
        ArbBin<FreqChar>* right = pq.top();
        pq.pop();

        FreqChar mergedFreqChar{'#', left->GetInfo().freq + right->GetInfo().freq};
        ArbBin<FreqChar>* mergedNode = new ArbBin<FreqChar>(mergedFreqChar);
        mergedNode->CuelgaSubarbolIzq(*left, dummy);
        mergedNode->CuelgaSubarbolDer(*right, dummy);
        pq.push(mergedNode);
    }

    if (!pq.empty()) {
        ArbBin<FreqChar>* topNode = pq.top();
        tree.SetInfo(topNode->GetInfo());
        tree.AgregaIzq(topNode->GetIzqArbBin().GetInfo(), dummy);
        tree.AgregaDer(topNode->GetDerArbBin().GetInfo(), dummy);
    }

    while (!pq.empty()) {
        delete pq.top();
        pq.pop();
    }
}

string obtenerCodigoHuffman(char c, ArbBin<NodoB<FreqChar>> tree) {
    if (tree.IsEmpty()) {
        return "";
    }

    ArbBin<NodoB<FreqChar>> subarbolIzquierdo = tree.GetIzqArbBin();
    if (!subarbolIzquierdo.IsEmpty() && subarbolIzquierdo.GetInfo().Getinfo().c == c) {
        return "0";
    } else if (!subarbolIzquierdo.IsEmpty()) {
        string leftCode = obtenerCodigoHuffman(c, subarbolIzquierdo);
        if (!leftCode.empty()) {
            return "0" + leftCode;
        }
    }

    ArbBin<NodoB<FreqChar>> subarbolDerecho = tree.GetDerArbBin();
    if (!subarbolDerecho.IsEmpty() && subarbolDerecho.GetInfo().Getinfo().c == c) {
        return "1";
    } else if (!subarbolDerecho.IsEmpty()) {
        string rightCode = obtenerCodigoHuffman(c, subarbolDerecho);
        if (!rightCode.empty()) {
            return "1" + rightCode;
        }
    }

    return "";
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
    uint16_t numDistinctChars;
    inputFile.read(reinterpret_cast<char*>(&numDistinctChars), sizeof(uint16_t));

    // Leer ci y fi para cada carácter y construir el mapa de frecuencias
    map<char, int> freq;
    for (uint16_t i = 0; i < numDistinctChars; ++i) {
        char c;
        int charFreq;
        inputFile.read(&c, sizeof(char));
        inputFile.read(reinterpret_cast<char*>(&charFreq), sizeof(int));
        freq[c] = charFreq;
    }

    // Leer w (longitud original del archivo)
    int originalLength;
    inputFile.read(reinterpret_cast<char*>(&originalLength), sizeof(int));

    // Construir el árbol de Huffman basado en las frecuencias
    construirArbol(freq);

    // Decodificar el contenido del archivo binario
    string decodedText;
    string bitBuffer;
    char byte;
    while (inputFile.read(&byte, sizeof(char))) {
        // Convertir el byte a una cadena de bits de 8 bits
        bitset<8> bits(byte);
        string bitString = bits.to_string();
        
        // Agregar los bits al búfer de bits
        bitBuffer += bitString;

        // Decodificar los caracteres a partir del búfer de bits
        while (bitBuffer.size() >= 8) {
            // Tomar los primeros 8 bits del búfer
            string byteBits = bitBuffer.substr(0, 8);
            
            // Convertir los bits a un byte
            bitset<8> charBits(byteBits);
            char decodedChar = static_cast<char>(charBits.to_ulong());

            // Agregar el carácter decodificado al texto
            decodedText += decodedChar;

            // Eliminar los primeros 8 bits del búfer
            bitBuffer.erase(0, 8);
        }
    }

    inputFile.close();

    // Verificar la longitud del texto decodificado
    if (decodedText.size() != static_cast<size_t>(originalLength)) {
        cerr << "Error: Longitud del texto decodificado no coincide con la longitud original." << endl;
        return "\0"; // Devolver una cadena nula para indicar un error
    }

    // Escribir el texto decodificado en un archivo de texto
    ofstream outputFile("decoded.txt");
    if (!outputFile.is_open()) {
        cerr << "Error al abrir el archivo de texto para escribir la decodificación." << endl;
        return "\0"; // Devolver una cadena nula para indicar un error
    }

    outputFile << decodedText;
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
      
        string huffmanCode = obtenerCodigoHuffman(c, tree);
        encodedText += huffmanCode;
    }

    int numDistinctChars = freq.size();

    ofstream outputFile("encoded.bin", ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error al abrir el archivo binario para escribir la codificación." << endl;
        return "\0";
    }

    outputFile.write(reinterpret_cast<char*>(&numDistinctChars), sizeof(uint16_t));

    for (const auto& pair : freq) {
        char c = pair.first;
        int freq = pair.second;
        outputFile.write(&c, sizeof(char));
        outputFile.write(reinterpret_cast<char*>(&freq), sizeof(int));
    }

    int originalLength = textContent.size();

    outputFile.write(reinterpret_cast<char*>(&originalLength), sizeof(int));

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
