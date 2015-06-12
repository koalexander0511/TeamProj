
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
    template <class ItemType>
    class DijkstraVertex
    {
    private:
        Vertex<ItemType> vert; // the vertex
        int distTo; // distance to this vertex
        DijkstraVertex prevVertex; // DijkstraVertex that brought you to this one
        bool isFinished;
    public:
        DijkstraVertex(LabelType label) : vert(label), distTo(INT_MAX), prevVertex(0), isFinished(false) {}
        void setDist(int d) {distTo = d; }
        void setPrev(DijkstraVertex& pv) {prevVertex = pv; }
    };

private:
    DijkstraVertex<LabelType> startPoint;
    DijkstraVertex<LabelType> endPoint;

    vector<DijkstraVertex<LabelType>* > finishedVertices; // store dynamically
    vector<DijkstraVertex<LabelType>* > unfinishedVertices; // store dynamically

    void prepareVertices(LabelType& x);

    bool applyDijkstra();

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
};

template <class LabelType>
Dijkstra<LabelType>::Dijkstra()
{

}

template <class LabelType>
Dijkstra<LabelType>::~Dijkstra()
{

}

template <class LabelType>
void Dijkstra<LabelType>::prepareVertices(LabelType& x)
{
    unfinishedVertices.push_back(new DijkstraVertex<LabelType>(x));
}

template <class LabelType>
bool Dijkstra<LabelType>::applyDijkstra()
{
    this->depthFirstTraversal(startPoint, prepareVertices);
    // now unfinishedVertices is filled with pointers to DijkstraVertices


    return false;
}

template <class LabelType>
bool Dijkstra<LabelType>::add(LabelType start, LabelType end, int edgeWeight)
{
    // document change with undoStack, then add() as usual
    // (modify later if Dijkstra::add() requires it)

    return LinkedGraph<LabelType>::add(start, end, edgeWeight);
}

template <class LabelType>
bool Dijkstra<LabelType>::remove(LabelType start, LabelType end)
{
    // document change with undoStack, then add() as usual
    // (change later if Dijkstra::add() requires it)

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
    // check if it's valid
    // then set
    return false;
}

template <class LabelType>
bool Dijkstra<LabelType>::setEndPoint(LabelType endP)
{
    // check if it's valid
    // then set
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






