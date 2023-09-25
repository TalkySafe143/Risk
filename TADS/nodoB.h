//
// Created by talkysafe143 on 24/09/23.
//

#ifndef PROYECTO_NODOB_H
#define PROYECTO_NODOB_H


template <class T>
class NodoB
{
    public:
        NodoB(){izq = der = nullptr;}
        NodoB(T m_info ){info = m_info;izq = nullptr;  der = nullptr;}
        NodoB(T m_info, NodoB<T> m_izq  , NodoB<T> m_der  ){info = m_info;izq = m_izq;  der = m_der;}
        T Getinfo() { return info; }
        NodoB<T> * GetIzq() { return izq; }
        NodoB<T> * GetDer() { return der; }

        void GetIzq(NodoB<T> *&i) {  i = izq; }
        void GetDer(NodoB<T> *&d) { d = der; }

        void Setinfo(T val) { info = val; }
        void SetIzq(NodoB<T> *val) { izq  = val; }
        void SetDer(NodoB<T> *val) { der = val; }
        void CopyTree(NodoB<T> *TreePtr, NodoB<T>*&NewTreePtr)
        {
            // recorrido en preorden
            if (TreePtr != 0)
            {
                // copiar el nodo
                NewTreePtr = new NodoB<T>(TreePtr->info);
                CopyTree(TreePtr->izq,NewTreePtr->izq);
                CopyTree(TreePtr->der,NewTreePtr->der);
            }
            else
                NewTreePtr = 0; // copiar Ã¡rbol vacio
        }

    private:
        T info; //!< Member variable "info"
        NodoB<T> *izq; //!< Member variable "izq"
        NodoB<T> *der; //!< Member variable "der"
};


#endif //PROYECTO_NODOB_H

//#ifndef NODO_H_INCLUDED
//#define NODO_H_INCLUDED
//
//template <class T>
//class Nodo
//{
//	private:
//        T info;
//        Nodo<T> *sig;
//    public:
//            Nodo();
//            Nodo(T , Nodo<T> *sig = nullptr);
//        void setInfo(T );
//        void setSig(Nodo<T> *);
//        T   getInfo() const;
//        Nodo<T> *getSig() const;
//};
//
//#endif // NODO_H_INCLUDED
