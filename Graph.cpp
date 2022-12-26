#include <iostream>
#include "Graph.h"

Graph::Graph(bool hasDir) {
    this->hasDir = hasDir;
}

void Graph::addNode(std::string& airportCode, Airport* airport) {
    nodes.insert({airportCode, {{}, airport,false}});
}

void Graph::addEdge(string& source, string& dest, string& airline) {
    auto sourceIt = nodes.find(source);
    auto destIt = nodes.find(dest);

    if (sourceIt != nodes.end() && destIt != nodes.end() && source != dest) {

        bool hasEdge = false;
        for (auto& edge : sourceIt->second.flights) {
            if (edge.destAirport == dest) {
                edge.airlines.insert(airline);
                hasEdge = true;
                break;
            }
        }

        if (!hasEdge) {
            sourceIt->second.flights.push_back({dest, {airline}});
        }

        if (!hasDir) {
            destIt->second.flights.push_back({source, {airline}});
        }
    }
}
void Graph::printGraph() {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        std::cout << it->first << " => ";
        for (auto it2 = it->second.flights.begin(); it2 != it->second.flights.end(); ++it2) {
            std::cout << it2->destAirport << " ";
        }
        cout << endl;
    }
}