#ifndef GRAFO_BASICO_EDGE_H
#define GRAFO_BASICO_EDGE_H

#include "defines.hpp"
using namespace std;

class Edge
{
private:
    size_t target_id;
    size_t origin_id;
    Edge *next_edge;
    float weight;
    bool directed;
    bool marked;

public:
    Edge(size_t targetId, size_t originId, float weight);
    ~Edge();

    size_t getTargetId();
    Edge *getNextEdge();
    void setNextEdge(Edge *nextEdge);
    size_t getOriginId();
    float getWeight();
    void setWeight(float weight);
    bool isDirected();
    void setDirected(bool directed);
    bool isMarked();
    void setMarked(bool marked);
};

#endif /* GRAFO_BASICO_EDGE_H */
