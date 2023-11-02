//
// Created by SERGIO on 8/10/2023.
// patico


#include "ArbBin.h"
#include "nodoB.h"
#include <stdexcept>


// Constructor con info
// Constructor con info y los dos subarboles
template <class T>
ArbBin<T>::ArbBin(const T &info, const ArbBin<T> &izq, const ArbBin<T> &der) {
    raiz = new NodoB<T>(info, izq.raiz, der.raiz);
}

// Destructor     ------Lo hago con destroyTree???????


/*
// Constructor copia
template <class T>
ArbBin<T>::ArbBin(const ArbBin<T> &other) {
    CopyTree(other.raiz, raiz);
}

// Sobrecarga del operador de asignación
template <class T>
ArbBin<T> &ArbBin<T>::operator=(const ArbBin<T> &other) {
    if (this != &other) {
        DestroyTree(raiz);
        CopyTree(other.raiz, raiz);
    }
    return *this;
}
*/
// Retorna true si el arbol esta vacío, false en caso contrario
template <class T>
bool ArbBin<T>::IsEmpty() const {
    return raiz == nullptr;
}

// Retorna solo la información que se encuentra en la raíz
template <class T>
T ArbBin<T>::GetInfo() const {
    if (raiz != nullptr) {
        return raiz->Getinfo();
    } else {
        throw std::runtime_error("El arbol está vacio");
    }
}

// Retorna una copia del subárbol izquierdo
template <class T>
ArbBin<T> ArbBin<T>::GetIzqArbBin() {
    if (raiz != nullptr) {
        return ArbBin<T>(raiz->GetIzq());
    } else {
        throw std::runtime_error("El arbol esta vacio");
    }
}

// Retorna una copia del subárbol derecho
template <class T>
ArbBin<T> ArbBin<T>::GetDerArbBin() {
    if (raiz != nullptr) {
        return ArbBin<T>(raiz->GetDer());
    } else {
        throw std::runtime_error("El arbol esta vacio");
    }
}

// Cambia la información que se encuentra en la raíz
template <class T>
void ArbBin<T>::SetInfo(const T info) {
        raiz->Setinfo(info);
}

// Agrega una hoja a la derecha de la raíz
template <class T>
void ArbBin<T>::AgregaDer(const T info, bool &ok) {
    if (raiz != nullptr) {
        NodoB<T> *nuevo = new NodoB<T>(info);
        raiz->SetDer(nuevo);
        ok = true;
    } else {
        ok = false;
    }
}

// Agrega una hoja a la izquierda de la raíz
template <class T>
void ArbBin<T>::AgregaIzq(const T info, bool &ok) {
    if (raiz != nullptr) {
        NodoB<T> *nuevo = new NodoB<T>(info);
        raiz->SetIzq(nuevo);
        ok = true;
    } else {
        ok = false;
    }
}

// Descuelga el subárbol izquierdo
template <class T>
void ArbBin<T>::DescuelgaSubarbolIzq(ArbBin<T> &subarbol, bool &ok) {
    if (raiz != nullptr) {
        subarbol.raiz = raiz->GetIzq();
        raiz->SetIzq(nullptr);
        ok = true;
    } else {
        ok = false;
    }
}

// Descuelga el subárbol derecho
template <class T>
void ArbBin<T>::DescuelgaSubarbolDer(ArbBin<T> &subarbol, bool &ok) {
    if (raiz != nullptr) {
        subarbol.raiz = raiz->GetDer();
        raiz->SetDer(nullptr);
        ok = true;
    } else {
        ok = false;
    }
}

// Cuelga el subárbol izquierdo
template <class T>
void ArbBin<T>::CuelgaSubarbolIzq(ArbBin<T> &subarbol, bool &ok) {
    if (raiz != nullptr && subarbol.raiz != nullptr) {
        raiz->SetIzq(subarbol.raiz);
        subarbol.raiz = nullptr;
        ok = true;
    } else {
        ok = false;
    }
}

// Cuelga el subárbol derecho
template <class T>
void ArbBin<T>::CuelgaSubarbolDer(ArbBin<T> &subarbol, bool &ok) {
    if (raiz != nullptr && subarbol.raiz != nullptr) {
        raiz->SetDer(subarbol.raiz);
        subarbol.raiz = nullptr;
        ok = true;
    } else {
        ok = false;
    }
}



///-----------    RECORRIDOS DEL ARBOL   -----------///
//recorrido en pre-orden
template <class T>
void ArbBin<T>::PreorderT(void (*Visit)(T AnItem)) {
    Preorder(raiz, Visit);
}
template <class T>
void ArbBin<T>::Preorder(NodoB<T>* TreePtr, void (*Visit)(T)) {
    if (TreePtr != nullptr) {
        Visit(TreePtr->Getinfo()); // Realiza la operación en el nodo actual

        Preorder(TreePtr->GetDer(), Visit); // recursion subárbol derecho
        Preorder(TreePtr->GetIzq(), Visit); // recursion subárbol izquierdo
    }
}

// Recorrido en orden del árbol
template <class T>
void ArbBin<T>::InorderT(void (*Visit)(T AnItem)) {
    Inorder(raiz, Visit);
}
template <class T>
void ArbBin<T>::Inorder(NodoB<T>* TreePtr, void (*Visit)(T)) {
    if (TreePtr != nullptr) {
        Inorder(TreePtr->GetDer(), Visit);
        Visit(TreePtr->Getinfo()); // Realizar la operación en el nodo actual
        Inorder(TreePtr->GetIzq(), Visit);
    }
}

// Recorrido en postorden del árbol
template <class T>
void ArbBin<T>::PosorderT(void (*Visit)(T AnItem)) {
    Posorder(raiz, Visit);
}
template <class T>
void ArbBin<T>::Posorder(NodoB<T>* TreePtr, void (*Visit)(T)) {
    if (TreePtr != nullptr) {
        Posorder(TreePtr->GetDer(), Visit);
        Posorder(TreePtr->GetIzq(), Visit);
        Visit(TreePtr->Getinfo()); // Realizar la operación en el nodo actual
    }
}

///-----------    PROTECTED   -----------///
//
// Constructor que recibe un puntero a un nodo como raíz
// Copia el árbol a partir del nodo apuntado por NodePtr
template <class T>
void ArbBin<T>::CopyTree(NodoB<T> *TreePtr, NodoB<T> *&NewTreePtr) const {
    if (TreePtr != nullptr) {
        NewTreePtr = new NodoB<T>(TreePtr->Getinfo());
        CopyTree(TreePtr->GetIzq(), NewTreePtr->GetIzq());
        CopyTree(TreePtr->GetDer(), NewTreePtr->GetDer());
    } else {
        NewTreePtr = nullptr;
    }
}


template<class T>
void ArbBin<T>::GetDerArbBin(ArbBin<T> &) {

}

template<class T>
void ArbBin<T>::GetIzqArbBin(ArbBin<T> &) {

}

template<class T>
ArbBin<T> ArbBin<T>::operator=(const ArbBin<T> &other) {
    return ArbBin<T>();
}

template<class T>
ArbBin<T>::ArbBin(const ArbBin<T> &other) {

}