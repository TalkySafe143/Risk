//
// Created by talkysafe143 on 15/10/23.
//

#ifndef PROYECTO_NODOG_H
#define PROYECTO_NODOG_H

#include<iostream>
#include<list>

using namespace std;

template<class T>
class NodoG {
private:
    T data;
    list< pair< reference_wrapper<NodoG<T>> , int > > adj;
    bool visited=false;
public:
    bool operator ==(NodoG<T> a) {return a.data == this->data;}
    bool getVisited();
    void setVisited(bool value);
    T &getData();
    void setData(T &d);
    list<pair<reference_wrapper<NodoG<T>>, int>> & getAdj();
    void addVertex(NodoG<T> &n, int cost);
    void deleteVertex(NodoG<T> del);
    pair< reference_wrapper<NodoG<T>>, int > getAdjacentVertex(NodoG<T> s);
    void changeArcCost(NodoG<T> &a, int c);
};




#endif //PROYECTO_NODOG_H
