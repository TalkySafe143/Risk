//
// Created by talkysafe143 on 15/10/23.
//

#ifndef PROYECTO_GRAFO_H
#define PROYECTO_GRAFO_H

#include<iostream>
#include<list>
#include "NodoG.h"
using namespace std;

template <class T>
class Grafo
{
private:
    list< NodoG<T> > vertices;//la posición en la lista corresponde al número de vértice.
public:
    Grafo();  //Constructor por omisión
    void InsVertice( T v ); //Agregar vértice v al final de la lista de vértices con Infovertice de tipo T.
    void InsArco(int v1, int v2,int c); // inserta un arco con costo c entre los vértices v1 y v2
    void ElimArco(int v1,int v2); //Elimina el arco entre los vértices v1 y v2
    void ElimVertice(int v);//Elimina el vértice v del Grafo
    void MarcarVertice(int v);//Marca el vértice v
    void DesmarcarVertice(int v);//Desmarca el vértice v
    void DesmarcarGrafo();// desmarca todos los vértices del grafo
    bool MarcadoVertice(int v);//Retorna true si el vértice v está marcado, false en caso contrario
    T InfoVertice(int v);// Retorna la información de Tipo T almacenada en el vértice
    int OrdenGrafo() const; // Retorna el número de vértices que tiene el grafo
    int CostoArco(int v1,int v2) ;//Retorna el costo del arco existente entre v1 y v2. Sino existe un arco entre los dos vértices retorna -1
    list<int> sucesores(int v1) ;// retorna la lista enteros con los sucesores del vértice v1
    list< T >  getvertices() ; // Retorna una lista con los vértices del grafo. Cada elemento de la lista tiene la información (tipo T) de cada vértice
};


#endif //PROYECTO_GRAFO_H
