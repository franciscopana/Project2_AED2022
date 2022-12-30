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
    double distance;
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
    list<Edge> getEdges(string& airportCode);
    vector<vector<Node*>> bfsWithNSteps(string& srcAirport, int n, set<string>& airlines);
    vector<stack<Node*>> bfsWithDest(string &srcAirport, string &destAirport, set<string> &airlines);
    vector<Node*> dijkstra(string &srcAirport, string &destAirport, set<string> &airlines);
    bool hasAirport(const string& airportCode) const;
};


#endif //TRABALHO2_GRAPH_H