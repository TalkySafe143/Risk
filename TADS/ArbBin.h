    //
// Created by SERGIO on 8/10/2023.
//

#ifndef ARBBINTAD_ARBBIN_H
#define ARBBINTAD_ARBBIN_H
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
    bool IsEmpty() const ;  //Retorna true si el arbol esta vacio filas en caso contario
    T GetInfo() const ;     //Retorna la informacion que se encuentra en la raiz
    ArbBin<T> GetIzqArbBin(); // retorna Copia de subarbol Izquierdo
    ArbBin<T> GetDerArbBin(); // retorna copia de subarbol derecho

    /* me devuelve el mismo arbol --son metodos sobrecargados-- */
    void GetIzqArbBin(ArbBin<T> &); // subarbol Izquierdo retorna la direccion de lo que tiene el arbool
    void GetDerArbBin(ArbBin<T> &); // subarbol derecho

    void SetInfo(const T ); //Cambia la informacion que se encuentra en la raiz
    void AgregaDer(const T , bool &); //Agrega una hoja a la derecha  de la raiz
    void AgregaIzq(const T , bool &);  //Agrega una hoja a la izquierda de la raiz
    void DescuelgaSubarbolIzq(ArbBin<T>& , bool &); // descuelga el subarbol izquierdo --revisar
    void DescuelgaSubarbolDer(ArbBin<T>& , bool &); //descuelga el subarbol derecho    --revisar
    void CuelgaSubarbolIzq(ArbBin<T>& , bool &); // cuelga el subarbol izquierdo
    void CuelgaSubarbolDer(ArbBin<T>& , bool &); //cuelga el subarbol derecho

    void PreorderT(void (*Visit)(T AnItem)); //toma un puntero a la funcion visit  que toma un argumento AnItem y no retorna nada
    void InorderT(void (*Visit)(T AnItem));
    void PosorderT(void (*Visit)(T AnItem));

protected:

    ArbBin(NodoB<T> *NodePtr); // constructor
    void CopyTree(NodoB<T> *, NodoB<T> *& ) const; //Copia el arbol a partir de lo que apunta la raiz
    void DestroyTree(NodoB<T>  *& ); //Destruye el arbol liberando el espacio
    void Preorder(NodoB<T>* TreePtr, void (*Visit)(T ));
    void Inorder(NodoB<T>* TreePtr, void (*Visit)(T ));
    void Posorder(NodoB<T>* TreePtr, void (*Visit)(T ));

private:
    NodoB<T> *raiz; //!< Member variable raiz"
};
#endif //ARBBINTAD_ARBBIN_H
