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

vector<stack<Node*>> Graph::bfsWithDest(string &srcAirport, string &destAirport) {
    vector<vector<pair<Node *, Node *>>> adjacent;

    auto srcNodeIt = nodes.find(srcAirport);
    Node *srcNode = &srcNodeIt->second;
    auto destNodeIt = nodes.find(destAirport);
    Node *destNode = &destNodeIt->second;

    long distance = 0;
    int numberPaths = 0;
    bool found = false;

    pair<Node *, Node *> srcPair = {nullptr, srcNode};
    adjacent.push_back({srcPair});
    srcNode->visited = true;
    queue<pair<Node *, int>> q;
    q.emplace(srcNode, distance);

    while (!q.empty() && !found) {
        Node* u = q.front().first;
        distance = q.front().second;
        q.pop();
        distance++;
        for (auto &edge: u->edges) {
            auto nextNodeIt = nodes.find(edge.destAirport);
            Node* nextNode = &nextNodeIt->second;
            if (!nextNode->visited) {
                pair<Node*, Node*> nextPair = {u, nextNode};
                q.emplace(nextNode, distance);
                nextNode->visited = true;
                if (adjacent.size() > distance) {
                    adjacent[distance].push_back(nextPair);
                }else{
                    adjacent.push_back({nextPair});
                }
            }
            if (nextNode == destNode) {
                found = true;
                numberPaths++;
                nextNode->visited = false;
            }
        }
    }

    vector<stack<Node*>> paths;
    if(found) {
        for (int i = 0; i < numberPaths; i++) {
            stack<Node*> path;
            path.push(destNode);
            while(path.top() != srcNode) {
                vector<pair<Node*, Node*>> &adjacentNodes = adjacent[distance];
                for(auto& pair : adjacentNodes) {
                    if(pair.second == path.top()) {
                        path.push(pair.first);
                        distance--;
                        adjacentNodes.erase(remove(adjacentNodes.begin(), adjacentNodes.end(), pair), adjacentNodes.end());
                        break;
                    }
                }
            }
            paths.push_back(path);
        }
    }
    return paths;
}

bool Graph::hasAirport(const string& airportCode) const{
    return nodes.find(airportCode) != nodes.end();
}