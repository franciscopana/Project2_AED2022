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

    unsigned distance = 1;
    bool found = false;
    queue<pair<Node*, Node*>> solutions;

    pair<Node *, Node *> srcPair = {nullptr, srcNode};
    adjacent.push_back({srcPair});
    srcNode->visited = true;

    for(int i = 0; i < distance; i++){
        adjacent.emplace_back();
        for(auto& pair : adjacent[i]){
            for(auto& edge : pair.second->edges){
                auto nextNodeIt = nodes.find(edge.destAirport);
                Node* nextNode = &nextNodeIt->second;
                if(!nextNode->visited){
                    nextNode->visited = true;
                    adjacent[distance].emplace_back(pair.second, nextNode);
                    if(nextNode == destNode){
                        found = true;
                        solutions.emplace(pair.second, nextNode);
                        nextNode->visited = false;
                    }
                }
            }
        }
        if(!found)
            distance++;
    }

    vector<stack<Node*>> paths;

    while(!solutions.empty()){
        int i = distance - 1;
        stack<Node*> path;
        pair<Node*, Node*> solPair = solutions.front();
        Node* current = solPair.second;
        Node* previous = solPair.first;
        path.push(current);
        while(previous != nullptr){
            for(auto& pair : adjacent[i]){
                if(pair.second == previous){
                    current = pair.second;
                    previous = pair.first;
                    path.push(current);
                    break;
                }
            }
            i--;
        }
        paths.push_back(path);
        solutions.pop();
    }

    for(auto& airportsVector : adjacent) {
        for(auto& pair : airportsVector) {
            pair.second->visited = false;
        }
    }
    return paths;
}

bool Graph::hasAirport(const string& airportCode) const{
    return nodes.find(airportCode) != nodes.end();
}