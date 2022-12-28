
#ifndef TRABALHO2_GRAPH_H
#define TRABALHO2_GRAPH_H

#include <string>
#include <set>
#include <list>
#include <unordered_map>
#include "Airline.h"
#include "Airport.h"

using namespace std;

struct Edge {
    string destAirport;
    set<string> airlines;
};

struct Node {
    Airport* airport;
    list<Edge> edges;
    bool visited;
};

class Graph {
private:
    unordered_map<string, Node> nodes;

public:
    Graph() = default;

    // Adders
    void addNode(string& airportCode,Airport* airport);
    void addEdge(string& source, string& dest, string& airline);

    // Searchers
    list<vector<Node*>> bfsWithNSteps(string& srcAirport, int n);

    // Printers
    void printGraph() const;
    void printEdges(string& airportCode) const;
};


#endif //TRABALHO2_GRAPH_H
