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
/**
 * @struct Edge
 * @brief represents a connection between two nodes of the graph. In this context, it represents the connections betwwen
 * 2 aiports, containing the airlines that do this flight and the distance between the 2 airports
 */
struct Edge {
    string destAirport;
    set<string> airlines;
    double distance;
};

/**
 * @struct Node
 * @brief represents a airport (from Aiport class), containing a list of edges. This list is all the flights that depart from
 * this airport
 */
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

/**
 * @struct vertexDistance
 */
struct vertexDistance{
    Node* node;
    double distance;

    bool operator<(const vertexDistance& other) const{
        return distance > other.distance;
    }
};

/**
 * @class Graph
 * @brief Graph class, where the airports are the nodes and the edges are the flights between them.
 * @details The graph is implemented using an adjacency list. The nodes are stored in a hash table, where the key is the airport code and the value is a Node struct.
 */

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
    const unordered_map<string, Node>& getNodes();
    list<Edge> getEdges(string& airportCode);
    vector<vector<Node*>> bfsWithNSteps(string& srcAirport, int n, set<string>& airlines);
    vector<pair<stack<Node*>, int>> bfsWithDest(vector<string> &srcAirports, vector<string> &destAirport, set<string> &airlines);
    bool hasAirport(const string& airportCode) const;

    // Getters
    Airport* getAirport(const string& airportCode) const;
};


#endif //TRABALHO2_GRAPH_H