//
// Created by talkysafe143 on 15/10/23.
//

#include "Grafo.h"
#include "NodoG.cpp"

template< class T >
void Grafo<T>::InsVertice(T &v) {

    for (auto node: Grafo<T>::vertices) {
        if (node.getData() == v) return;
    }

    NodoG<T> *nuevo = new NodoG<T>();
    nuevo->setData(v);

    Grafo<T>::vertices.push_back(*nuevo);
}

template< class T >
void Grafo<T>::InsArco(int v1, int v2, int c) {
    int i = 0, j = 0;

    for (auto &vertexFrom: Grafo<T>::vertices) {
        if (i == v1) {
            for (auto &vertexTo: Grafo<T>::vertices) {
                if (j == v2) {
                    vertexFrom.addVertex(vertexTo, c);
                    break;
                }
                j++;
            }
            break;
        }
        i++;
    }
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

    for (auto &[node, cost]: adjVertex) {
        int i = 0;
        for (auto vertex: Grafo<T>::vertices) {
            if (node.get().getData() == vertex.getData()) {
                ans.push_back(i);
                break;
            }
            i++;
        }
    }

    return ans;
}

template< class T >
list< T > &Grafo<T>::getvertices() {
    list<T> vertex;
    for (auto node: Grafo<T>::vertices) {
        vertex.push_back(node.getData());
    }

    return vertex;
}

template< class T >
list<Grafo<T>> Grafo<T>::componentesConexos(Grafo<T> graph) {
        list< Grafo<T> > ans;
        while (true) {
            int sz = graph.getvertices().size();
            bool valid = true;
            int choose = 0;
            for (int i = 0; i < sz; i++) {
                if (!graph.MarcadoVertice(i)) { valid = false; choose = i; break; }
            }

            if (valid) break;

            Grafo<T> nuevo;

            // BFS
            queue<int> q;
            q.push(choose);
            graph.MarcarVertice(choose);
            while (!q.empty()) {
                int s = q.front(); q.pop();
                nuevo.InsVertice(graph.InfoVertice(s));
                for (auto v: graph.sucesores(s)) {
                    if (graph.MarcadoVertice(v)) continue;
                    graph.MarcarVertice(v);
                    q.push(v);
                }
            }

            // Agregar las aristas al nuevo Grafo
            for (int i = 0; i < nuevo.getvertices().size(); i++) {
                for (int j = 0; j < nuevo.getvertices().size(); j++) {
                    if (graph.CostoArco(i, j) != -1) nuevo.InsArco(i, j, graph.CostoArco(i, j));
                }
            }

            ans.push_back(nuevo);
        }

        return ans;
}


template<class T>
void Grafo<T>::changeArcCost(int from, int to, int cNew) {
    auto fromIt = Grafo<T>::vertices.begin();
    auto toIt = Grafo<T>::vertices.begin();

    advance(fromIt, from);
    advance(toIt, to);

    fromIt->changeArcCost(*toIt, cNew);
}

template<class T>
list<NodoG<T>>& Grafo<T>::getVerticesNode() {
    return Grafo<T>::vertices;
}


template< class T >
void Grafo<T>::Dijkstra(int S, vector<int> &dist, vector<int>&parent) {

    for (int i = 0; i < dist.size(); i++) {
        dist[i] = 1e6;
        parent[i] = -1;
    }

    priority_queue<pair<int, int>, vector< pair<int, int> >, greater<pair<int, int>>> pq;
    dist[S] = 0;
    pq.push(make_pair(0, S));
    while (!pq.empty()) {
        pair<int, int> V = pq.top(); pq.pop();
        int dist_V = V.first;
        int vertex_V = V.second;
        if (dist_V > dist[vertex_V]) continue;

        auto itSuc = this->getVerticesNode().begin();
        advance(itSuc, vertex_V);

        for (auto arc: itSuc->getAdj()) {
            auto node = arc.first;
            auto len = arc.second;
            int to = 0;
            for (auto n: this->getVerticesNode()) {
                if (n == node) break;
                to++;
            }

            if (dist[vertex_V] + len < dist[to]) {
                dist[to] = dist[vertex_V] + len;
                parent[to] = vertex_V;
                pq.push(make_pair(dist[to], to));
            }
        }
    }
}