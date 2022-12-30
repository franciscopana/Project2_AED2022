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

vector<stack<pair<Node*,Node*>>> Graph::bfsWithDest(string &srcAirport, string &destAirport) {
    vector<stack<pair<Node*, Node*>>> paths;
    auto srcNodeIt = nodes.find(srcAirport);
    pair<Node*, Node*> srcPair = {nullptr, &srcNodeIt->second};
    queue<pair<Node*, Node*>> q;
    q.emplace(srcPair);
    srcNodeIt->second.visited = true;
    bool found = false;
    int maxDistance = nodes.size(), distance = 0;
    while(!q.empty() && !found && maxDistance >= distance) {
        distance = maxDistance;
        auto u = q.front();
        q.pop();
        for(auto& edge : u.second->edges) {
            auto destNodeIt = nodes.find(edge.destAirport);
            if(!destNodeIt->second.visited) {
                pair<Node*, Node*> destPair = {u.second, &destNodeIt->second};
                q.emplace(destPair);
                destNodeIt->second.visited = true;
                if(destNodeIt->second.airport->getCode() == destAirport) {
                    stack<pair<Node*, Node*>> s;
                    s.push(destPair);
                    paths.push_back(s);
                    maxDistance = distance + 1;
                    found = true;
                }
            }
        }
    }
// Reset visited flag on all nodes
for (auto& node : nodes) {
    node.second.visited = false;
}

// Create path by tracing back from the destination airport to the source airport
for (stack<pair<Node*, Node*>>& path : paths) {
    while (path.top().first != nullptr) {
        Node* previous = path.top().first;
        for (auto& edge : previous->edges) {
            auto destNodeIt = nodes.find(edge.destAirport);
            if (destNodeIt->second.airport->getCode() == path.top().second->airport->getCode()) {
                pair<Node*, Node*> destPair = {previous, &destNodeIt->second};
                path.push(destPair);
                break;
            }
        }
    }
}

return paths;
}