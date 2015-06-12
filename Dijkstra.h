
#pragma once

#include <fstream>
#include <climits>
#include <vector>
#include "LinkedGraph.h"
#include "Vertex.h"
#include "Edge.h"
#include "LinkedStack.h"

using namespace std;

template <class LabelType>
class Dijkstra : public LinkedGraph<LabelType>
{
    // nested class for LinkedStack element store:
    // operation type(add/remove), start, and end.

private:
    Vertex<LabelType> startPoint;
    Vertex<LabelType> endPoint;
    vector<int> dist;
    vector<Vertex<LabelType> > finishedVertecies;
    vector<Vertex<LabelType> > unfinishedVertices;
    LinkedStack<LabelType>* undoStack;

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
    void writeToFile(ofstream&) const;
};

template <class LabelType>
Dijkstra<LabelType>::Dijkstra()
{

    undoStack = new LinkedStack<LabelType>();
}

template <class LabelType>
Dijkstra<LabelType>::~Dijkstra()
{

    delete undoStack;
}

template <class LabelType>
bool Dijkstra<LabelType>::add(LabelType start, LabelType end, int edgeWeight)
{
    // document change with undoStack, then add() as usual
    // (change later if Dijkstra::add() requires it)

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
void Dijkstra<LabelType>::writeToFile(ofstream& fout) const
{
    fout << "Dijkstra write to file. " << endl;
}






