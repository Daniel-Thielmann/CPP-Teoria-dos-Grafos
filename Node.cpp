#include "Node.hpp"

using namespace std;

Node::Node(size_t id)
    : first_edge(nullptr), last_edge(nullptr), nextNode(nullptr), id(id), inDegree(0), outDegree(0), edgeCount(0), unmarkedEdgeCount(0), weight(0), marked(false)
{
}

Node::~Node()
{
    Edge *current = this->first_edge;
    while (current != nullptr) {
        Edge *nextEdge = current->getNextEdge();
        delete current;
        current = nextEdge;
    }
}

Edge* Node::getFirstEdge()
{
    return this->first_edge;
}

Edge* Node::getLastEdge()
{
    return this->last_edge;
}

size_t Node::getId()
{
    return this->id;
}

size_t Node::getInDegree()
{
    return this->inDegree;
}

size_t Node::getOutDegree()
{
    return this->outDegree;
}

float Node::getWeight()
{
    return this->weight;
}

void Node::setWeight(float weight)
{
    this->weight = weight;
}

Node* Node::getNextNode()
{
    return this->nextNode;
}

void Node::setNextNode(Node *nextNode)
{
    this->nextNode = nextNode;
}

size_t Node::getEdgeCount()
{
    Edge *current = this->first_edge;
    this->edgeCount = 0;
    while (current != nullptr) {
        this->edgeCount++;
        current = current->getNextEdge();
    }
    return this->edgeCount;
}

bool Node::hasEdgeTo(size_t targetId)
{
    return this->searchEdge(targetId) != nullptr;
}

bool Node::isMarked()
{
    return this->marked;
}

void Node::setMarked(bool marked)
{
    this->marked = marked;
}

void Node::decrementUnmarkedEdgeCount()
{
    if (this->unmarkedEdgeCount > 0) {
        this->unmarkedEdgeCount--;
    }
}

void Node::incrementDegree(bool directed)
{
    if (directed) {
        this->outDegree++;
    } else {
        this->inDegree++;
        this->outDegree++;
    }
}

void Node::incrementEdgeCount()
{
    this->edgeCount++;
}

void Node::decrementNum_edges()
{
    if (this->edgeCount > 0) {
        this->edgeCount--;
    }
}

Edge* Node::searchEdge(size_t targetId)
{
    Edge *current = this->first_edge;
    while (current != nullptr) {
        if (current->getTargetId() == targetId) {
            return current;
        }
        current = current->getNextEdge();
    }
    return nullptr;
}

void Node::addEdge(Node *target, bool directed, float weight)
{
    Edge *new_edge = new Edge(target->getId(), this->getId(), weight);
    new_edge->setDirected(directed);

    if (this->first_edge == nullptr) {
        this->first_edge = new_edge;
        this->last_edge = new_edge;
    } else {
        this->last_edge->setNextEdge(new_edge);
        this->last_edge = new_edge;
    }
}

void Node::removeEdge(Node *target)
{
    Edge *prev = nullptr;
    Edge *current = this->first_edge;

    while (current != nullptr) {
        if (current->getTargetId() == target->getId()) {
            if (prev == nullptr) {
                this->first_edge = current->getNextEdge();
            } else {
                prev->setNextEdge(current->getNextEdge());
            }
            if (current == this->last_edge) {
                this->last_edge = prev;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->getNextEdge();
    }
}

void Node::removeEdgeById(size_t id)
{
    Node *target = new Node(id);
    this->removeEdge(target);
    delete target;
}

void Node::removeAllEdges()
{
    Edge *current = this->first_edge;
    while (current != nullptr) {
        Edge *next_edge = current->getNextEdge();
        delete current;
        current = next_edge;
    }
    this->first_edge = nullptr;
    this->last_edge = nullptr;
}

vector<size_t> Node::getNeighborhood() const
{
    vector<size_t> neighborhood;
    Edge *current = this->first_edge;

    while (current != nullptr) {
        neighborhood.push_back(current->getTargetId());
        current = current->getNextEdge();
    }
    return neighborhood;
}
