#include "Edge.hpp"

using namespace std;

Edge::Edge(size_t targetId, size_t originId, float weight)
    : target_id(targetId), origin_id(originId), weight(weight), next_edge(nullptr), directed(false), marked(false)
{
}

Edge::~Edge()
{
    this->next_edge = nullptr;
}

size_t Edge::getTargetId()
{
    return this->target_id;
}

Edge *Edge::getNextEdge()
{
    return this->next_edge;
}

void Edge::setNextEdge(Edge *nextEdge)
{
    this->next_edge = nextEdge;
}

size_t Edge::getOriginId()
{
    return this->origin_id;
}

float Edge::getWeight()
{
    return this->weight;
}

void Edge::setWeight(float weight)
{
    this->weight = weight;
}

bool Edge::isDirected()
{
    return this->directed;
}

void Edge::setDirected(bool directed)
{
    this->directed = directed;
}

bool Edge::isMarked()
{
    return this->marked;
}

void Edge::setMarked(bool marked)
{
    this->marked = marked;
}
