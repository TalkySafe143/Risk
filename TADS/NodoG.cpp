//
// Created by talkysafe143 on 15/10/23.
//

#include "NodoG.h"

template< class T >
T &NodoG<T>::getData() {
    return NodoG<T>::data;
}

template< class T >
void NodoG<T>::setData(T &d) {
    NodoG<T>::data = d;
}

template< class T >
list<pair<reference_wrapper<NodoG<T>>, int>> & NodoG<T>::getAdj() {
    return NodoG<T>::adj;
}

template< class T >
void NodoG<T>::addVertex(NodoG<T> &n, int cost) {
    NodoG<T>::adj.push_back(pair<reference_wrapper<NodoG<T>>, int>(n, cost));
}

template<class T>
void NodoG<T>::deleteVertex(NodoG<T> del) {
    auto it = NodoG<T>::adj.begin();
    for (; it != NodoG<T>::adj.end(); it++) {
        if (it->first.getData() == del.getData()) {
            NodoG<T>::adj.erase(it);
            return;
        }
    }
}

template<class T>
void NodoG<T>::setVisited(bool value) {
    NodoG<T>::visited = value;
}

template<class T>
bool NodoG<T>::getVisited() {
    return NodoG<T>::visited;
}

template<class T>
pair<reference_wrapper<NodoG<T>>, int>  NodoG<T>::getAdjacentVertex(NodoG<T> s) {
    for (auto &node: NodoG<T>::adj) {
        if (node.first.get().getData() == s.getData()) return node;
    }

    NodoG<T> a;
    return pair<reference_wrapper<NodoG<T>>, int>(a, -1);
}

template<class T>
void NodoG<T>::changeArcCost(NodoG<T> &a, int c) {
    for (auto &node: NodoG<T>::adj) {
        if (node.first.get() == a) {
            node.second = c;
            break;
        }
    }
}
