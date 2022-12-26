#include "Graph.h"

Graph::Graph(bool hasDir) {
    this->hasDir = hasDir;
}

void Graph::addNode(int &airportCode, Airport *airport) {
    nodes.insert({airportCode, {airport, {}, false}});
}

void Graph::void addEdge(string& source, string& dest, string& airline) {
    auto sourceIt = nodes.find(source);
    auto destIt = nodes.find(dest);

    if (sourceIt != nodes.end() && destIt != nodes.end() && source != dest) {
        sourceIt->second.flights.push_back({dest, {airline}});
        if (!hasDir) {
            destIt->second.flights.push_back({source, {airline}});
        }
    }
}
