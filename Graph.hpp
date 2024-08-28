#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "defines.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include <vector>
#include <set>
#include <unordered_map>

class Graph {
public:
    Graph(bool weightedEdge, bool weightedNode, bool directed);
    ~Graph();

    size_t getOrder() const;
    size_t getNumEdges() const;
    size_t getTotalEdges() const;
    size_t getUncoveredEdges() const;
    void setUncoveredEdges(size_t num);
    void setWeightedEdge(bool weighted);
    void setWeightedNode(bool weighted);
    void setDirected(bool directed);
    bool isWeightedEdge() const;
    bool isWeightedNode() const;
    bool isDirected() const;
    size_t getGraphRadius();       
    size_t getGraphDiameter();
    bool loadFromFile(const std::string& filename);  
    
    std::vector<size_t> shortestPathFloyd(size_t start, size_t end);
    std::vector<size_t> getGraphCenter();
    std::vector<size_t> getGraphPeripheral();
    std::vector<size_t> getArticulationPoints();
    
    void addNode(size_t id);
    void addEdge(size_t originId, size_t targetId, float weight);
    void removeNode(size_t id);
    void removeEdge(size_t originId, size_t targetId);
    void removeAllNodes();
    void removeAllEdges();
    Node* getNode(size_t id) const;
    std::vector<size_t> bfs(size_t startNodeId);
    std::vector<size_t> dfs(size_t startNodeId);
    std::vector<size_t> shortestPath(size_t startNodeId, size_t targetNodeId);
    void printGraph();
    void printAdjacentList();

private:
    size_t order;
    size_t num_edge;
    size_t total_edge;
    size_t uncovered_edge;
    size_t getGraphRadiusUtil();  
    size_t getGraphDiameterUtil(); 
    std::vector<size_t> shortestPathUtil(size_t startNodeId, size_t targetNodeId); 
    Node* first_node;
    Node* last_node;
    bool weighted_edge;
    bool weighted_node;
    bool directed;

    std::vector<size_t> bfsSearch(size_t startNodeId);
    std::vector<size_t> dfsSearch(size_t startNodeId, std::set<size_t>& visited);
    void articulationDFS(size_t u, std::unordered_map<size_t, bool>& visited,
                         std::unordered_map<size_t, size_t>& disc, std::unordered_map<size_t, size_t>& low,
                         std::unordered_map<size_t, size_t>& parent, std::unordered_map<size_t, bool>& articulation,
                         size_t& time);
    void findArticulationPoints(size_t u, std::unordered_map<size_t, bool>& visited,
                                std::unordered_map<size_t, size_t>& discoveryTime, std::unordered_map<size_t, size_t>& lowTime,
                                std::unordered_map<size_t, size_t>& parent, std::vector<size_t>& articulationPoints, size_t& time);
};

#endif // GRAPH_H_INCLUDED
