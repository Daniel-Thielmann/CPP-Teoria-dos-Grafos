#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "defines.hpp"
#include "Edge.hpp"
#include <vector>

using namespace std;

class Node {
private:
    Edge *first_edge;
    Edge *last_edge;
    Node *nextNode;

    size_t id;
    size_t inDegree;
    size_t outDegree;
    size_t edgeCount;
    size_t unmarkedEdgeCount;
    float weight;
    bool marked;

public:
    Node(size_t id);  
    ~Node();

    void setNextNode(Node *nextNode);
    float getWeight();
    void setWeight(float weight);
    size_t getUnmarkedEdgeCount();
    void setUnmarkedEdgeCount(size_t count);
    Edge *getFirstEdge();
    Edge *getLastEdge();
    Node *getNextNode();
    size_t getId();
    size_t getInDegree();
    size_t getOutDegree();
    size_t getEdgeCount();
    void setMarked(bool marked);

    bool hasEdgeTo(size_t targetId);
    bool isMarked();
    void decrementUnmarkedEdgeCount();
    void incrementDegree(bool directed);
    void incrementEdgeCount();
    void decrementNum_edges();

    Edge *searchEdge(size_t targetId);

    void addEdge(Node *target, bool directed, float weight);
    void removeEdge(Node *target);
    void removeEdgeById(size_t id);
    void removeAllEdges();

    vector<size_t> getNeighborhood() const;

    std::vector<std::pair<size_t, float>> edges; 
};

#endif // NODE_H_INCLUDED
