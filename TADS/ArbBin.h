//
// Created by talkysafe143 on 24/09/23.
//

#ifndef PROYECTO_ARBBIN_H
#define PROYECTO_ARBBIN_H
#include "nodoB.h"


template <class T>
class ArbBin
{
    public:
        ArbBin(); //constructor por omisión
        ArbBin(const T &); //constructor con info
        ArbBin(const T &, const ArbBin<T> & , const ArbBin<T> &); //constructor con info y los dos subarboles
        ~ArbBin(); //destructor
        ArbBin(const ArbBin<T> & other); //constructor copia
        ArbBin& operator=(const ArbBin<T>& other); //sobrecarga del igual
        bool IsEmpty() const ;//Retorna true si el rabol esta vacÃ­o flas en caso contario
        T GetInfo() const ;//Retorna la informaciÃ³n que se encuentra en la raiz
        ArbBin<T> GetIzqArbBin(); // retorna Copia de subarbol Izquierdo
        ArbBin<T> GetDerArbBin(); // retorna copia de subarbol derecho
        void GetIzqArbBin(ArbBin<T> &); // subarbol Izquierdo
        void GetDerArbBin(ArbBin<T> &); // subarbol derecho
        void SetInfo(const T ); //Cambia la informaciÃ³n que se encuentra en la raiz
        void AgregaDer(const T , bool &); //Agrega una hoja a la drerecha  de la raiz
        void AgregaIzq(const T , bool &);  //Agrega una hoja a la izquierda de la raiz
        void DescuelgaSubarbolIzq(ArbBin<T>& , bool &); // descuelga el subarbol izquierdo
        void DescuelgaSubarbolDer(ArbBin<T>& , bool &); //descuelga el subarbol derecho
        void CuelgaSubarbolIzq(const ArbBin<T>& , bool &); // descuelga el subarbol izquierdo
        void CuelgaSubarbolDer(const ArbBin<T>& , bool &); //descuelga el subarbol derecho

        void PreorderT(void (*Visit)(T AnItem));
        void InorderT(void (*Visit)(T AnItem));
        void PosorderT(void (*Visit)(T AnItem));

    protected:

        ArbBin(NodoB<T> *NodePtr); // constructor
        void CopyTree(NodoB<T> *, NodoB<T> *& ) const; //Copia el arbol a partir de lso que apunta la raiz
        void DestroyTree(NodoB<T>  *& ); //Destruye el arbol liberando el espacio
        void Preorder(NodoB<T>* TreePtr, void (*Visit)(T ));
        void Inorder(NodoB<T>* TreePtr, void (*Visit)(T ));
        void Posorder(NodoB<T>* TreePtr, void (*Visit)(T ));

    private:
        NodoB<T> *raiz; //!< Member variable raiz"
};


#endif //PROYECTO_ARBBIN_H
