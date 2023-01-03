#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
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
        sourceIt->second.edges.push_back({dest, {airline}, sourceIt->second.airport->getDistance(destIt->second.airport)});
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

const list<Node*> Graph::getNodes() {
    list<Node*> nodesList;
    for (auto& node : nodes) {
        nodesList.push_back(&node.second);
    }
    return nodesList;
}

list<Edge> Graph::getEdges(string& airportCode) {
    auto it = nodes.find(airportCode);
    if (it != nodes.end()) {
        return it->second.edges;
    }
    return {};
}

bool includes(set<string> &set1, set<string> &set2){
    for(auto &element : set1){
        if(set2.find(element) != set2.end()){
            return true;
        }
    }
    return false;
}

vector<vector<Node*>> Graph::bfsWithNSteps(string& srcAirport, int n, set<string>& airlines){
    vector<vector<Node*>> airports;

    int numSteps = 0;
    auto srcNodeIt = nodes.find(srcAirport);
    queue<pair<Node*, int>> q;
    q.emplace(&srcNodeIt->second, numSteps);
    srcNodeIt->second.visited = true;
    airports.push_back({&srcNodeIt->second});

    while (!q.empty() && (numSteps = q.front().second) < n) {
        Node* u = q.front().first;
        q.pop();
        numSteps++;
        for (auto& edge : u->edges) {
            if(!airlines.empty() && !includes(airlines, edge.airlines)){
                continue;
            }

            auto destNodeIt = nodes.find(edge.destAirport);
            if (!destNodeIt->second.visited) {
                q.emplace(&destNodeIt->second, numSteps);
                destNodeIt->second.visited = true;
                if(airports.size() > numSteps) {
                    airports[numSteps].push_back(&destNodeIt->second);
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

vector<pair<stack<Node*>, int>> Graph::bfsWithDest(vector<string> &srcAirports, vector<string> &destAirport,set<string> &airlines) {
    vector<pair<stack<Node*>, int>> allPaths;

    vector<Node*> srcNodes;
    for(auto& srcAirport : srcAirports){
        auto srcNodeIt = nodes.find(srcAirport);
        srcNodes.push_back(&srcNodeIt->second);
    }

    vector<Node*> destNodes;
    for(auto& dAirport : destAirport){
        auto destNodeIt = nodes.find(dAirport);
        destNodes.push_back(&destNodeIt->second);
    }

    for(auto srcNode: srcNodes){
        for(auto destNode: destNodes){
            for (auto &node: nodes) {
                node.second.visited = false;
            }
            vector<vector<pair<Node *, Node *>>> adjacent;
            unsigned steps = 1;
            bool found = false;
            queue<pair<Node*, Node*>> solutions;

            pair<Node *, Node *> srcPair = {nullptr, srcNode};
            adjacent.push_back({srcPair});
            srcNode->visited = true;

            for(int i = 0; i < steps; i++){
                adjacent.emplace_back();
                bool loop = false;
                for(auto& pair : adjacent[i]){
                    loop = true;
                    for(auto& edge : pair.second->edges){
                        if(airlines.empty() || includes(airlines, edge.airlines)){
                            auto nextNodeIt = nodes.find(edge.destAirport);
                            Node* nextNode = &nextNodeIt->second;
                            if(!nextNode->visited){
                                nextNode->visited = true;
                                adjacent[steps].emplace_back(pair.second, nextNode);
                                if(nextNode == destNode){
                                    found = true;
                                    solutions.emplace(pair.second, nextNode);
                                    nextNode->visited = false;
                                }
                            }
                        }
                    }
                }
                if(!found && loop) steps++;
            }

            while (!solutions.empty()) {
                int i = steps - 1;
                int distance = 0;
                stack<Node*> path;
                pair<Node*, Node*> solPair = solutions.front();
                Node *current = solPair.second;
                Node *previous = solPair.first;
                path.push(current);
                while (previous != nullptr) {
                    distance += current->airport->getDistance(previous->airport);
                    for (auto &pair: adjacent[i]) {
                        if (pair.second == previous) {
                            current = pair.second;
                            previous = pair.first;
                            path.push(current);
                            break;
                        }
                    }
                    i--;
                }
                allPaths.emplace_back(path, distance);
                solutions.pop();
            }
        }
    }
    sort(allPaths.begin(), allPaths.end(),
         [](pair<stack<Node*>, int> &a, pair<stack<Node*>, int> &b){
             if(a.first.size() == b.first.size()){
                 return a.second < b.second;
             }
             return a.first.size() < b.first.size();
         });
    return allPaths;
}


vector<Node*> Graph::dijkstra(string &srcAirport, string &destAirport, set<string> &airlines){
    unordered_map<string, double> distances;
    list<Node*> visitedNodes;
    for(auto& node : nodes){
        distances[node.first] = INFINITY;
    }
    distances[srcAirport] = 0;

    priority_queue<vertexDistance> priorityQueue;
    priorityQueue.emplace(vertexDistance{&nodes[srcAirport], 0});

    unordered_map<string, Node*> previous;

    while (!priorityQueue.empty()){
        vertexDistance current = priorityQueue.top();
        priorityQueue.pop();

        if(current.node->visited)
            continue;
        current.node->visited = true;
        visitedNodes.push_back(current.node);

        for(Edge& edge : current.node->edges){
            if(!airlines.empty() && !includes(airlines, edge.airlines)){
                continue;
            }

            double distance = current.distance + edge.distance;
            if(distance < distances[edge.destAirport]){
                distances[edge.destAirport] = distance;
                previous[edge.destAirport] = current.node;
                priorityQueue.emplace(vertexDistance{&nodes[edge.destAirport], distance});
            }
        }
        if(current.node->airport->getCode() == destAirport)
            break;
    }
    vector<Node*> path;
    Node* current = &nodes[destAirport];
    while(current != nullptr){
        path.push_back(current);
        current = previous[current->airport->getCode()];
    }
    if(path.size() <2) {path.clear();}
    reverse(path.begin(), path.end());

    for(auto& node : visitedNodes){node->visited = false;}
    return path;
}

bool Graph::hasAirport(const string& airportCode) const{
    return getAirport(airportCode) != nullptr;
}

Airport* Graph::getAirport(const string& airportCode) const{
    auto it = nodes.find(airportCode);
    if(it != nodes.end()){
        Airport* airport = it->second.airport;
        return airport;
    }
    return nullptr;
}