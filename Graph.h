
#ifndef TRABALHO2_GRAPH_H
#define TRABALHO2_GRAPH_H

#include <string>
#include <vector>
#include <set>
#include <list>
#include <unordered_map>
#include <stack>
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
    Node* getNode(string& airportCode);
    vector<vector<Node*>> bfsWithNSteps(string& srcAirport, int n);
    vector<stack<Node*>> bfsWithDest(string &srcAirport, string &destAirport);
};


#endif //TRABALHO2_GRAPH_H
