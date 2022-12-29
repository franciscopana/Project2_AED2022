#include <iostream>
#include <queue>
#include <utility>
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
void Graph::printEdges(string &airportCode) const {
    auto it = nodes.find(airportCode);
    if (it != nodes.end()) {
        cout << ">> Source Airport: "; it->second.airport->printHeader(); cout << endl;
        cout << ">> Destination Airports:" << endl;
        for (const auto & edge : it->second.edges) {
            cout << "     ";
            string destAirportCode = edge.destAirport;
            auto destIt = nodes.find(destAirportCode);
            destIt->second.airport->printHeader();
            cout << "\t|\tAirlines: ";
            for (const auto & airline : edge.airlines) {
                cout << airline << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
}

vector<vector<Node*>> Graph::bfsWithNSteps(string &srcAirport, int n=-1) {
    vector<vector<Node*>> airports;

    int distance = 0, currentDistance = 0;
    auto srcNodeIt = nodes.find(srcAirport);
    queue<pair<Node*, int>> q;
    q.emplace(&srcNodeIt->second, distance);
    srcNodeIt->second.visited = true;
    airports.push_back({&srcNodeIt->second});

    while (!q.empty() && (distance = q.front().second) <= n) {
        if(distance > currentDistance) {
            airports.emplace_back();
            currentDistance = distance;
        }
        Node* u = q.front().first;
        q.pop();
        for (auto& edge : u->edges) {
            auto destNodeIt = nodes.find(edge.destAirport);
            if (!destNodeIt->second.visited) {
                q.emplace(&destNodeIt->second, distance + 1);
                destNodeIt->second.visited = true;
                airports.back().push_back(&destNodeIt->second);
            }
        }
    }

    for(auto& airportsVector : airports) {
        for(auto& node : airportsVector) {
            node->visited = false;
        }
    }
    return airports;
}
