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

    set<string> getAirlinesTo(string destAirport){
        for(Edge& edge : edges){
            if(edge.destAirport == destAirport){
                return edge.airlines;
            }
        }
        return set<string>();
    }
};

class Graph {
private:
    unordered_map<string, Node> nodes;

public:
    Graph() = default;

    void addNode(string& airportCode,Airport* airport);
    void addEdge(string& source, string& dest, string& airline);

    vector<vector<Node*>> bfsWithNSteps(string& srcAirport, int n, set<string>& airlines);
    vector<pair<stack<Node*>, int>> bfsWithDest(vector<string> &srcAirports, vector<string> &destAirport, set<string> &airlines);
    bool hasAirport(const string& airportCode) const;

    Node* getNode(string& airportCode);
    const unordered_map<string, Node>& getNodes();
    list<Edge> getEdges(string& airportCode);
    Airport* getAirport(const string& airportCode) const;
};


#endif //TRABALHO2_GRAPH_H