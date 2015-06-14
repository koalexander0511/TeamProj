
#pragma once

#include <fstream>
#include <climits>
#include <vector>
#include "LinkedGraph.h"
#include "Vertex.h"
#include "Edge.h"

using namespace std;

template <class LabelType>
class Dijkstra : public LinkedGraph<LabelType>
{
    // nested class for Dijkstra vertex
    // keep track of previous vertex in path, and distance to there
    class DijkstraVertex
    {
    private:
        Vertex<LabelType> vert; // the vertex
        int distTo; // distance to this vertex
        DijkstraVertex* prevVertex; // DijkstraVertex that brought you to this one
        bool isFinished;
    public:
        DijkstraVertex() : vert(0), distTo(INT_MAX), prevVertex(0), isFinished(false) {}
        DijkstraVertex(LabelType label) : vert(label), distTo(INT_MAX), prevVertex(0), isFinished(false) {}
        void setDist(int d) {distTo = d; }
        void setPrev(DijkstraVertex& pv) {prevVertex = pv; }
        Vertex<LabelType> getVertex() const {return vert; }
        LabelType getLabel() const {return vert.getLabel(); }
    };

private:
    DijkstraVertex* startPoint;
    DijkstraVertex* endPoint;

    vector<DijkstraVertex* > finishedVertices; // store dynamically
    vector<DijkstraVertex* > unfinishedVertices; // store dynamically

    //bool applyDijkstra();

public:
    Dijkstra();
    Dijkstra(const Dijkstra<LabelType>&);
    ~Dijkstra();

    bool add(LabelType start, LabelType end, int edgeWeight = 0);
    bool remove(LabelType start, LabelType end);
    void undo();

    bool setStartPoint(LabelType);
    bool setEndPoint(LabelType);

    int distanceTo(LabelType) const;

    void writeToFile(ofstream&) const;

    bool applyDijkstra();
};

template <class LabelType>
Dijkstra<LabelType>::Dijkstra()
{
    startPoint = 0;
    endPoint = 0;
}

template <class LabelType>
Dijkstra<LabelType>::~Dijkstra()
{
    delete startPoint;
    delete endPoint;
}

template <class LabelType>
bool Dijkstra<LabelType>::applyDijkstra()
{
    // unfinished vertices is filled with dij vertecices

    // startPoint has not been set
    if(!startPoint)
        return false;

    startPoint->setDist(0);
    finishedVertices.push_back(startPoint);

    int numNeighbors = 0;

    //while(finishedVertices.size() < unfinishedVertices.size()) {
        numNeighbors = this->vertices.getItem(finishedVertices.back()->getLabel())->getNumberOfNeighbors();
        for(int i = 0; i < numNeighbors; i++) {
            // for each unfinished neighbor, update distance/prev vertex
        }
    //}

    return false;
}

template <class LabelType>
bool Dijkstra<LabelType>::add(LabelType start, LabelType end, int edgeWeight)
{
    // document change with undoStack, then add() as usual
    // (modify later if Dijkstra::add() requires it)
    if(!this->vertices.contains(start))
        unfinishedVertices.push_back(new DijkstraVertex(start));
    if(!this->vertices.contains(end))
        unfinishedVertices.push_back(new DijkstraVertex(end));

    return LinkedGraph<LabelType>::add(start, end, edgeWeight);
}

template <class LabelType>
bool Dijkstra<LabelType>::remove(LabelType start, LabelType end)
{
    // document change with undoStack, then add() as usual
    // (change later if Dijkstra::add() requires it)
    // removed from un/finishedVertices as well

    return LinkedGraph<LabelType>::remove(start, end);
}

template <class LabelType>
void Dijkstra<LabelType>::undo()
{
    // peek most recent addition to the undoStack
    // and apply opposite(add/remove) to graph, then pop stack
}

template <class LabelType>
bool Dijkstra<LabelType>::setStartPoint(LabelType startP)
{
    if(!this->vertices.contains(startP))
        return false;
    startPoint = new DijkstraVertex(startP);
    return false;
}

// may not need
template <class LabelType>
bool Dijkstra<LabelType>::setEndPoint(LabelType endP)
{

    return false;
}

template <class LabelType>
int Dijkstra<LabelType>::distanceTo(LabelType x) const
{
    // check if x is in the graph
    // then retrieve correct distance from startPoint to x

    return -1;
}

template <class LabelType>
void Dijkstra<LabelType>::writeToFile(ofstream& fout) const
{
    fout << "Dijkstra write to file. " << endl;
}






