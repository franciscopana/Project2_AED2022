
#ifndef TRABALHO2_GRAPH_H
#define TRABALHO2_GRAPH_H

#include <string>
#include <set>
#include <list>
#include <unordered_map>
#include "Airline.h"
#include "Airport.h"

using namespace std;

class Graph {
private:
    struct Edge {
        string destAirport;
        set<string> airlines;
    };

    struct Node {
        string airport;
        list<Edge> flights;
    };

    bool hasDir;
    set<Node> nodes;

public:
    Graph(bool hasDir = true);
    void addEdge(string& source, string& dest, string& airline);
};


#endif //TRABALHO2_GRAPH_H
