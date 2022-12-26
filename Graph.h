
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
        Airport* airport;
        list<Edge> flights;
        bool visited;
    };

    bool hasDir;
    unordered_map<std::string, Node> nodes;

public:
    Graph(bool hasDir = true);
    void addNode(string& airportCode,Airport* airport);
    void addEdge(string& source, string& dest, string& airline);

    void printGraph() const;
};


#endif //TRABALHO2_GRAPH_H
