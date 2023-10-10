//
// Created by talkysafe143 on 24/09/23.
//

#ifndef PROYECTO_NODOB_H
#define PROYECTO_NODOB_H


template <class T>
class NodoB
{
    private:
        T info; //!< Member variable "info"
        NodoB<T> *izq; //!< Member variable "izq"
        NodoB<T> *der; //!< Member variable "der"
    public:
        NodoB();//constructor
        NodoB(T m_info );//constructor con info
        NodoB(T m_info, NodoB<T> m_izq  , NodoB<T> m_der  );//constructor
        T Getinfo();//Devuelve la info de un nodo
        NodoB<T> * GetIzq();//Devuelve sub-arbol izquierdo
        NodoB<T> * GetDer();//Devuelve sub-arbol derecho

        void GetIzq(NodoB<T> *&i);//Obtener por referncia el nodo de la izquierda
        void GetDer(NodoB<T> *&d);//Obtener por referncia el nodo de la derecha

        void Setinfo(T val); //Establece el valor info de un nodo
        void SetIzq(NodoB<T> *val);//Asigna el puntero izquierdo a un nodo
        void SetDer(NodoB<T> *val);//Asigna el puntero derecho a un nodo
        void CopyTree(NodoB<T> *TreePtr, NodoB<T>*&NewTreePtr);//copia el arbol treePtr a NewTreePtr
};


#endif