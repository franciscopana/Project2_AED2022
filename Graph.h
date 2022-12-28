
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
        list<Edge> edges;
        bool visited;
    };

    unordered_map<string, Node> nodes;

public:
    Graph() = default;
    void addNode(string& airportCode,Airport* airport);
    void addEdge(string& source, string& dest, string& airline);

    void printGraph() const;
    void printEdges(string& airportCode) const;
    void bfsWithNSteps(string& srcAirport, int n);
};


#endif //TRABALHO2_GRAPH_H
