//
// Created by talkysafe143 on 24/09/23.
//

#include "nodoB.h"
#include <iostream>

template< class T >
NodoB<T>::NodoB() {
    this->izq = NULL;
    this->der = NULL;
}

template< class T>
NodoB<T>::NodoB(T m_info){
    this->info = m_info;
    this->izq = nullptr;
    this->der = nullptr;
}

template< class T>
NodoB<T>::NodoB(T m_info, NodoB<T> m_izq  , NodoB<T> m_der  ){
    this->info = m_info;
    this->izq = m_izq;
    this->der = m_der;
}

template< class T>
T NodoB<T>::Getinfo(){
    return this->info;
}

template< class T>
NodoB<T>* NodoB<T>::GetIzq(){
    return this->izq;
}

template< class T>
NodoB<T>* NodoB<T>::GetDer(){
    return this->der;
}

template< class T>
void NodoB<T>::GetIzq(NodoB<T> *&i){
    i = this->izq;
}

template< class T>
void NodoB<T>::GetDer(NodoB<T> *&d){
    d = this->der;
}

template< class T>
void NodoB<T>::Setinfo(T val){
    this->info = val;
}

template< class T>
void NodoB<T>::SetIzq(NodoB<T> *val){
    this->izq  = val;
}

template< class T>
void NodoB<T>::SetDer(NodoB<T> *val){
    this->der = val;
}

template< class T>
void NodoB<T>::CopyTree(NodoB<T> *TreePtr, NodoB<T>*&NewTreePtr){
    // recorrido en preorden
    if (TreePtr != 0)
    {
        // copiar el nodo
        NewTreePtr = new NodoB<T>(TreePtr->info);
        CopyTree(TreePtr->izq,NewTreePtr->izq);
        CopyTree(TreePtr->der,NewTreePtr->der);
    }
    else
        NewTreePtr = 0; // copiar arbol vacio
}