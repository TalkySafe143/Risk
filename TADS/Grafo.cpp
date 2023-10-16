//
// Created by talkysafe143 on 15/10/23.
//

#include "Grafo.h"

template< class T >
void Grafo<T>::InsVertice(T v) {

    for (auto node: Grafo<T>::vertices) {
        if (node.getData() == v) return;
    }

    NodoG<T> nuevo;
    nuevo.setData(v);

    Grafo<T>::vertices.push_back(nuevo);
}

template< class T >
void Grafo<T>::InsArco(int v1, int v2, int c) {
    auto vertexFrom = Grafo<T>::vertices.begin();
    auto vertexTo = Grafo<T>::vertices.begin();
    advance(vertexFrom, v1);
    advance(vertexTo, v2);

    if (vertexTo == Grafo<T>::vertices.end() ||
    vertexFrom == Grafo<T>::vertices.end()) return;

    vertexFrom->addVertex(*vertexTo, c);
}

template< class T >
void Grafo<T>::ElimArco(int v1, int v2) {
    auto vertexFrom = Grafo<T>::vertices.begin();
    auto vertexTo = Grafo<T>::vertices.begin();
    advance(vertexFrom, v1);
    advance(vertexTo, v2);

    if (vertexTo == Grafo<T>::vertices.end() ||
        vertexFrom == Grafo<T>::vertices.end()) return;

    vertexFrom->deleteVertex(*vertexTo);
}

template< class T >
void Grafo<T>::ElimVertice(int v) {
    auto vertexFind = Grafo<T>::vertices.begin();
    advance(vertexFind, v);
    if (vertexFind == Grafo<T>::vertices.end()) return;
    Grafo<T>::vertices.erase(vertexFind);
}

template< class T >
void Grafo<T>::MarcarVertice(int v) {
    auto vertexFind = Grafo<T>::vertices.begin();
    advance(vertexFind, v);

    if (vertexFind == Grafo<T>::vertices.end()) return;

    vertexFind->setVisited(true);
}

template< class T >
void Grafo<T>::DesmarcarVertice(int v) {
    auto vertexFind = Grafo<T>::vertices.begin();
    advance(vertexFind, v);

    if (vertexFind == Grafo<T>::vertices.end()) return;

    vertexFind->setVisited(false);
}

template< class T >
void Grafo<T>::DesmarcarGrafo() {
    for (auto &node: Grafo<T>::vertices) node.setVisited(false);
}

template< class T >
bool Grafo<T>::MarcadoVertice(int v) {
    auto vertexFind = Grafo<T>::vertices.begin();
    advance(vertexFind, v);

    if (vertexFind == Grafo<T>::vertices.end()) return false;

    return vertexFind->getVisited();
}

template< class T >
T Grafo<T>::InfoVertice(int v) {
    auto vertexFind = Grafo<T>::vertices.begin();
    advance(vertexFind, v);
    T a;
    if (vertexFind == Grafo<T>::vertices.end()) return a;

    return vertexFind->getData();
}

template< class T >
int Grafo<T>::OrdenGrafo() const {
    return Grafo<T>::vertices.size();
}

template< class T >
int Grafo<T>::CostoArco(int v1, int v2) {
    auto vertexFrom = Grafo<T>::vertices.begin();
    auto vertexTo = Grafo<T>::vertices.begin();
    advance(vertexFrom, v1);
    advance(vertexTo, v2);

    if (vertexTo == Grafo<T>::vertices.end() ||
        vertexFrom == Grafo<T>::vertices.end()) return -1;

    return vertexFrom->getAdjacentVertex(*vertexTo).second;
}

template< class T >
list<int> Grafo<T>::sucesores(int v1) {
    list<int> ans;
    auto vertexFind = Grafo<T>::vertices.begin();
    advance(vertexFind, v1);
    if (vertexFind == Grafo<T>::vertices.end()) return ans;
    auto adjVertex = vertexFind->getAdj();

    for (auto [node, cost]: adjVertex) {
        int i = 0;
        for (auto vertex: Grafo<T>::vertices) {
            if (node.getData() == vertex.getData()) {
                ans.push_back(i);
                break;
            }
            i++;
        }
    }

    return ans;
}

template< class T >
list< T > Grafo<T>::getvertices() {
    list<T> vertex;
    for (auto node: Grafo<T>::vertices) {
        vertex.push_back(node.getData());
    }

    return vertex;
}