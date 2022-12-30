#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include "Graph.h"


/*    Adders    */
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


/*    Searchers    */
Node* Graph::getNode(string& airportCode) {
    auto it = nodes.find(airportCode);
    if (it != nodes.end()) {
        return &it->second;
    }
    return nullptr;
}

vector<vector<Node*>> Graph::bfsWithNSteps(string &srcAirport, int n) {
    vector<vector<Node*>> airports;

    int distance = 0;
    auto srcNodeIt = nodes.find(srcAirport);
    queue<pair<Node*, int>> q;
    q.emplace(&srcNodeIt->second, distance);
    srcNodeIt->second.visited = true;
    airports.push_back({&srcNodeIt->second});

    while (!q.empty() && (distance = q.front().second) < n) {
        Node* u = q.front().first;
        q.pop();
        distance++;
        for (auto& edge : u->edges) {
            auto destNodeIt = nodes.find(edge.destAirport);
            if (!destNodeIt->second.visited) {
                q.emplace(&destNodeIt->second, distance);
                destNodeIt->second.visited = true;
                if(airports.size() > distance) {
                    airports[distance].push_back(&destNodeIt->second);
                } else {
                    airports.push_back({&destNodeIt->second});
                }
            }
        }
    }

    for(auto& airportsVector : airports) {
        sort(airportsVector.begin(), airportsVector.end(), [](Node* a, Node* b) {
            return a->airport->getCode() < b->airport->getCode();
        });
        for(auto& node : airportsVector) {
            node->visited = false;
        }
    }

    return airports;
}

vector<Node*> Graph::findPath(string &srcAirport, string &destAirport) {
    vector<Node*> path;
    unordered_map<string, vector<Node*>> paths;

    int distance = 0;
    auto srcNodeIt = nodes.find(srcAirport);
    queue<pair<Node*, int>> q;
    q.emplace(&srcNodeIt->second, distance);
    srcNodeIt->second.visited = true;
    paths[srcNodeIt->second.airport->getCode()] = {&srcNodeIt->second};

    while (!q.empty()) {
        Node* u = q.front().first;
        distance = q.front().second;
        q.pop();
        if (u->airport->getCode() == destAirport) {
            path = paths[u->airport->getName()];
            break;
        }
        for (auto& edge : u->edges) {
            auto destNodeIt = nodes.find(edge.destAirport);
            if (!destNodeIt->second.visited) {
                q.emplace(&destNodeIt->second, distance + 1);
                destNodeIt->second.visited = true;
                paths[destNodeIt->second.airport->getCode()] = paths[u->airport->getCode()];
                paths[destNodeIt->second.airport->getCode()].push_back(&destNodeIt->second);
            }
        }
    }

    // Reset visited flag on all nodes
    for (auto& node : nodes) {
        node.second.visited = false;
    }

    return path;
}



