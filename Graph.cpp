#include <cstddef> 
#include "Graph.hpp"
#include <set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

Graph::Graph(bool weightedEdge, bool weightedNode, bool directed)
    : order(0), num_edge(0), total_edge(0), uncovered_edge(0), first_node(nullptr), last_node(nullptr),
      weighted_edge(weightedEdge), weighted_node(weightedNode), directed(directed) {}

Graph::~Graph()
{
    removeAllNodes();
}

size_t Graph::getOrder() const
{
    return this->order;
}

size_t Graph::getNumEdges() const
{
    return this->num_edge;
}

size_t Graph::getTotalEdges() const
{
    return this->total_edge;
}

size_t Graph::getUncoveredEdges() const
{
    return this->uncovered_edge;
}

void Graph::setUncoveredEdges(size_t num)
{
    this->uncovered_edge = num;
}

void Graph::setWeightedEdge(bool weighted)
{
    this->weighted_edge = weighted;
}

void Graph::setWeightedNode(bool weighted)
{
    this->weighted_node = weighted;
}

void Graph::setDirected(bool directed)
{
    this->directed = directed;
}

bool Graph::isWeightedEdge() const
{
    return this->weighted_edge;
}

bool Graph::isWeightedNode() const
{
    return this->weighted_node;
}

bool Graph::isDirected() const
{
    return this->directed;
}

void Graph::addNode(size_t id)
{
    Node *new_node = new Node(id);
    if (this->first_node == nullptr)
    {
        this->first_node = new_node;
        this->last_node = new_node;
    }
    else
    {
        this->last_node->setNextNode(new_node);
        this->last_node = new_node;
    }
    this->order++;
}

void Graph::addEdge(size_t originId, size_t targetId, float weight)
{
    Node *origin = this->getNode(originId);
    Node *target = this->getNode(targetId);

    if (origin && target)
    {
        origin->addEdge(target, this->directed, weight);
        if (!this->directed)
        {
            target->addEdge(origin, this->directed, weight);
        }
        this->num_edge++;
        this->total_edge++;
    }
}

void Graph::removeNode(size_t id)
{
    Node *nodeToRemove = this->getNode(id);
    if (!nodeToRemove)
        return;

    Node *currentNode = this->first_node;
    while (currentNode)
    {
        currentNode->removeEdgeById(id);
        currentNode = currentNode->getNextNode();
    }

    if (nodeToRemove == this->first_node)
    {
        this->first_node = this->first_node->getNextNode();
        if (this->first_node == nullptr)
        {
            this->last_node = nullptr;
        }
    }
    else
    {
        Node *prevNode = this->first_node;
        while (prevNode && prevNode->getNextNode() != nodeToRemove)
        {
            prevNode = prevNode->getNextNode();
        }
        if (prevNode)
        {
            prevNode->setNextNode(nodeToRemove->getNextNode());
            if (nodeToRemove == this->last_node)
            {
                this->last_node = prevNode;
            }
        }
    }
    delete nodeToRemove;
    this->order--;
}

void Graph::removeEdge(size_t originId, size_t targetId)
{
    Node *origin = this->getNode(originId);
    Node *target = this->getNode(targetId);

    if (origin && target)
    {
        origin->removeEdge(target);
        if (!this->directed)
        {
            target->removeEdge(origin);
        }
        this->num_edge--;
    }
}

void Graph::removeAllNodes()
{
    Node *current = this->first_node;
    while (current != nullptr)
    {
        Node *nextNode = current->getNextNode();
        delete current;
        current = nextNode;
    }
    this->first_node = nullptr;
    this->last_node = nullptr;
    this->order = 0;
}

void Graph::removeAllEdges()
{
    Node *current = this->first_node;
    while (current != nullptr)
    {
        current->removeAllEdges();
        current = current->getNextNode();
    }
    this->num_edge = 0;
    this->total_edge = 0;
}

Node *Graph::getNode(size_t id) const
{
    Node *current = this->first_node;
    while (current != nullptr)
    {
        if (current->getId() == id)
        {
            return current;
        }
        current = current->getNextNode();
    }
    return nullptr;
}

vector<size_t> Graph::bfs(size_t startNodeId)
{
    return bfsSearch(startNodeId);
}

vector<size_t> Graph::dfs(size_t startNodeId)
{
    set<size_t> visited;
    return dfsSearch(startNodeId, visited);
}

vector<size_t> Graph::shortestPath(size_t startNodeId, size_t targetNodeId)
{
    return shortestPathUtil(startNodeId, targetNodeId);
}

size_t Graph::getGraphRadius()
{
    return getGraphRadiusUtil();
}

size_t Graph::getGraphDiameter() 
{
    return getGraphDiameterUtil();
}

void Graph::printGraph()
{
    Node *current = this->first_node;
    while (current != nullptr)
    {
        cout << "Node ID: " << current->getId() << " Edges: ";
        Edge *edge = current->getFirstEdge();
        while (edge != nullptr)
        {
            cout << edge->getTargetId() << " ";
            edge = edge->getNextEdge();
        }
        cout << endl;
        current = current->getNextNode();
    }
}

void Graph::printAdjacentList()
{
    Node *current = this->first_node;
    while (current != nullptr)
    {
        cout << "Node ID: " << current->getId() << " Adjacent Nodes: ";
        vector<size_t> neighborhood = current->getNeighborhood();
        for (size_t id : neighborhood)
        {
            cout << id << " ";
        }
        cout << endl;
        current = current->getNextNode();
    }
}

vector<size_t> Graph::bfsSearch(size_t startNodeId)
{
    vector<size_t> traversal;
    set<size_t> visited;
    queue<Node*> nodeQueue;

    Node* startNode = getNode(startNodeId);
    if (!startNode)
        return traversal;

    visited.insert(startNodeId);
    nodeQueue.push(startNode);

    while (!nodeQueue.empty())
    {
        Node* currentNode = nodeQueue.front();
        nodeQueue.pop();
        traversal.push_back(currentNode->getId());

        Edge* edge = currentNode->getFirstEdge();
        while (edge != nullptr)
        {
            size_t neighborId = edge->getTargetId();
            if (visited.find(neighborId) == visited.end())
            {
                visited.insert(neighborId);
                nodeQueue.push(getNode(neighborId));
            }
            edge = edge->getNextEdge();
        }
    }

    return traversal;
}

vector<size_t> Graph::dfsSearch(size_t startNodeId, set<size_t> &visited)
{
    vector<size_t> traversal;
    stack<Node*> nodeStack;

    Node* startNode = getNode(startNodeId);
    if (!startNode)
        return traversal;

    visited.insert(startNodeId);
    nodeStack.push(startNode);

    while (!nodeStack.empty())
    {
        Node* currentNode = nodeStack.top();
        nodeStack.pop();
        traversal.push_back(currentNode->getId());

        Edge* edge = currentNode->getFirstEdge();
        while (edge != nullptr)
        {
            size_t neighborId = edge->getTargetId();
            if (visited.find(neighborId) == visited.end())
            {
                visited.insert(neighborId);
                nodeStack.push(getNode(neighborId));
            }
            edge = edge->getNextEdge();
        }
    }

    return traversal;
}

vector<size_t> Graph::shortestPathUtil(size_t startNodeId, size_t targetNodeId)
{
    unordered_map<size_t, float> distances;
    unordered_map<size_t, size_t> previous;
    set<size_t> visited;
    priority_queue<pair<float, size_t>, vector<pair<float, size_t>>, greater<pair<float, size_t>>> minHeap;

    Node* startNode = getNode(startNodeId);
    if (!startNode)
        return {};

    for (Node* node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        distances[node->getId()] = numeric_limits<float>::infinity();
    }
    distances[startNodeId] = 0.0f;
    minHeap.push({0.0f, startNodeId});

    while (!minHeap.empty())
    {
        size_t currentNodeId = minHeap.top().second;
        minHeap.pop();

        if (visited.find(currentNodeId) != visited.end())
            continue;
        visited.insert(currentNodeId);

        Node* currentNode = getNode(currentNodeId);
        if (!currentNode)
            continue;

        Edge* edge = currentNode->getFirstEdge();
        while (edge != nullptr)
        {
            size_t neighborId = edge->getTargetId();
            float weight = edge->getWeight();
            if (distances[currentNodeId] + weight < distances[neighborId])
            {
                distances[neighborId] = distances[currentNodeId] + weight;
                previous[neighborId] = currentNodeId;
                minHeap.push({distances[neighborId], neighborId});
            }
            edge = edge->getNextEdge();
        }
    }

    vector<size_t> path;
    size_t current = targetNodeId;
    while (previous.find(current) != previous.end())
    {
        path.push_back(current);
        current = previous[current];
    }
    if (distances[targetNodeId] != numeric_limits<float>::infinity())
    {
        path.push_back(startNodeId);
        reverse(path.begin(), path.end());
    }
    return path;
}

size_t Graph::getGraphRadiusUtil()
{
    size_t radius = numeric_limits<size_t>::max();
    for (Node* node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        vector<size_t> distances = shortestPathUtil(node->getId(), node->getId());
        if (distances.size() < radius)
            radius = distances.size();
    }
    return radius;
}

size_t Graph::getGraphDiameterUtil()
{
    size_t diameter = 0;
    for (Node* node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        vector<size_t> distances = shortestPathUtil(node->getId(), node->getId());
        if (distances.size() > diameter)
            diameter = distances.size();
    }
    return diameter;
}

vector<size_t> Graph::shortestPathFloyd(size_t start, size_t end) {
    vector<vector<float>> dist(order, vector<float>(order, numeric_limits<float>::infinity()));
    vector<vector<size_t>> next(order, vector<size_t>(order, -1));
    
    for (Node* node = first_node; node != nullptr; node = node->getNextNode()) {
        size_t u = node->getId();
        dist[u][u] = 0;
        for (Edge* edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge()) {
            size_t v = edge->getTargetId();
            dist[u][v] = edge->getWeight();
            next[u][v] = v;
        }
    }

    for (size_t k = 0; k < order; ++k) {
        for (size_t i = 0; i < order; ++i) {
            for (size_t j = 0; j < order; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    vector<size_t> path;
    if (dist[start][end] == numeric_limits<float>::infinity()) {
        return path; 
    }

    size_t current = start;
    while (current != end) {
        path.push_back(current);
        current = next[current][end];
        if (current == -1) {
            return {}; 
        }
    }
    path.push_back(end);

    return path;
}

vector<size_t> Graph::getGraphCenter() {
    vector<size_t> centers;
    float minRadius = numeric_limits<float>::infinity();

    for (Node* node = first_node; node != nullptr; node = node->getNextNode()) {
        size_t nodeId = node->getId();
        float maxDistance = 0;
        for (Node* target = first_node; target != nullptr; target = target->getNextNode()) {
            size_t targetId = target->getId();
            if (nodeId != targetId) {
                vector<size_t> path = shortestPathFloyd(nodeId, targetId);
                float distance = path.size(); 
                if (distance == 0) {
                    maxDistance = numeric_limits<float>::infinity();
                    break;
                }
                maxDistance = max(maxDistance, distance);
            }
        }
        if (maxDistance < minRadius) {
            minRadius = maxDistance;
            centers.clear();
            centers.push_back(nodeId);
        } else if (maxDistance == minRadius) {
            centers.push_back(nodeId);
        }
    }

    return centers;
}

vector<size_t> Graph::getGraphPeripheral() {
    vector<size_t> periphery;
    float maxRadius = 0;

    for (Node* node = first_node; node != nullptr; node = node->getNextNode()) {
        size_t nodeId = node->getId();
        float maxDistance = 0;
        for (Node* target = first_node; target != nullptr; target = target->getNextNode()) {
            size_t targetId = target->getId();
            if (nodeId != targetId) {
                vector<size_t> path = shortestPathFloyd(nodeId, targetId);
                float distance = path.size(); 
                if (distance == 0) {
                    maxDistance = numeric_limits<float>::infinity();
                    break;
                }
                maxDistance = max(maxDistance, distance);
            }
        }
        if (maxDistance > maxRadius) {
            maxRadius = maxDistance;
            periphery.clear();
            periphery.push_back(nodeId);
        } else if (maxDistance == maxRadius) {
            periphery.push_back(nodeId);
        }
    }

    return periphery;
}

void Graph::articulationDFS(size_t u, unordered_map<size_t, bool>& visited, unordered_map<size_t, size_t>& disc,
                            unordered_map<size_t, size_t>& low, unordered_map<size_t, size_t>& parent,
                            unordered_map<size_t, bool>& articulation, size_t& time) {
    size_t children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (Edge* edge = getNode(u)->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge()) {
        size_t v = edge->getTargetId();
        if (!visited[v]) {
            ++children;
            parent[v] = u;
            articulationDFS(v, visited, disc, low, parent, articulation, time);
            low[u] = min(low[u], low[v]);

            if (parent[u] == -1 && children > 1) {
                articulation[u] = true;
            }
            if (parent[u] != -1 && low[v] >= disc[u]) {
                articulation[u] = true;
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

vector<size_t> Graph::getArticulationPoints() {
    unordered_map<size_t, bool> visited;
    unordered_map<size_t, size_t> disc, low, parent;
    unordered_map<size_t, bool> articulation;
    vector<size_t> articulationPoints;
    size_t time = 0;

    for (Node* node = first_node; node != nullptr; node = node->getNextNode()) {
        size_t u = node->getId();
        visited[u] = false;
        parent[u] = -1;
        articulation[u] = false;
    }

    for (Node* node = first_node; node != nullptr; node = node->getNextNode()) {
        size_t u = node->getId();
        if (!visited[u]) {
            articulationDFS(u, visited, disc, low, parent, articulation, time);
        }
    }

    for (const auto& pair : articulation) {
        if (pair.second) {
            articulationPoints.push_back(pair.first);
        }
    }

    return articulationPoints;
}

bool Graph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo: " << filename << std::endl;
        return false;
    }

    size_t numNodes, numEdges;
    bool weightedEdge;
    file >> numNodes >> numEdges >> weightedEdge;

    setWeightedEdge(weightedEdge);
    setWeightedNode(false); 

    for (size_t i = 0; i < numNodes; ++i) {
        addNode(i); 
    }

    size_t originId, targetId;
    float weight;
    for (size_t i = 0; i < numEdges; ++i) {
        if (weightedEdge) {
            file >> originId >> targetId >> weight;
            addEdge(originId, targetId, weight);
        } else {
            file >> originId >> targetId;
            addEdge(originId, targetId, 1.0f); 
        }
    }

    file.close();
    return true;
}

