#include <iostream>
#include "Graph.h"


void Graph::addNode(string& airportCode, Airport* airport) {
    nodes.insert({airportCode, {airport, {}, false}});
}

void Graph::addEdge(string& source, string& dest, string& airline) {
    auto sourceIt = nodes.find(source);
    auto destIt = nodes.find(dest);

    if (sourceIt != nodes.end() && destIt != nodes.end() && source != dest) {
        for (auto& edge : sourceIt->second.edges) {
            if (edge.destAirport == dest) {
                edge.airlines.insert(airline);
                return;
            }
        }
        sourceIt->second.edges.push_back({dest, {airline}});
    }
}

void Graph::printGraph() const {
    for (const auto & node : nodes) {
        cout << node.first << " => ";
        for (const auto & edge : node.second.edges) {
            std::cout << edge.destAirport << ": " << edge.airlines.size() << " airlines  |  ";
        }
        cout << endl;
    }
}
void Graph::printEdges(std::string &airportCode) const {
    auto it = nodes.find(airportCode);
    if (it != nodes.end()) {
        for (const auto & edge : it->second.edges) {
            std::cout << edge.destAirport << ": " << edge.airlines.size() << " airlines  |  ";
        }
        cout << endl;
    }
}