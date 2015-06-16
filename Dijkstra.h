
#pragma once

#include <fstream>
#include <climits>
#include <vector>
#include "LinkedGraph.h"
#include "Vertex.h"

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
    public:
        DijkstraVertex(LabelType label) : vert(label), distTo(INT_MAX), prevVertex(0) {}

        void setDist(int d) {distTo = d; }
        void setPrev(DijkstraVertex* pv) {prevVertex = pv; }
        int getDist() const { return distTo; }
        DijkstraVertex* getPrev() const { return prevVertex; }
        Vertex<LabelType> getVertex() const {return vert; }
        LabelType getLabel() const {return vert.getLabel(); }
    };

private:
    DijkstraVertex* startPoint;
    LabelType endPoint;

    vector<DijkstraVertex* > finishedVertices; // stored dynamically
    vector<DijkstraVertex* > unfinishedVertices; // stored dynamically

    bool applyDijkstra();

public:
    Dijkstra();
    ~Dijkstra();

    bool add(LabelType start, LabelType end, int edgeWeight = 0);
    bool remove(LabelType start, LabelType end);

    bool setStartPoint(LabelType);
    bool setEndPoint(LabelType);

    int distanceTo(LabelType);

    void writeToFile(ofstream&) const;
};

template <class LabelType>
Dijkstra<LabelType>::Dijkstra()
{
    startPoint = 0;
}

template <class LabelType>
Dijkstra<LabelType>::~Dijkstra()
{
    // delete the contents of unfinishedVertices and finishedVertices
	for (unsigned i = 0; i < unfinishedVertices.size(); i++) {
		delete unfinishedVertices[i];
	}
	for (unsigned i = 0; i < finishedVertices.size(); i++) {
		delete finishedVertices[i];
	}
    delete startPoint;
}

template <class LabelType>
bool Dijkstra<LabelType>::applyDijkstra()
{
    // unfinished vertices is filled with dij vertices
    // test if need to reset distTo INT_MAX every time, between multiple changes/applyDijkstra's

    // startPoint has not been set
    if(!startPoint)
        return false;

    startPoint->setDist(0);
    finishedVertices.push_back(startPoint); // start at start point, then push back closest neighbor as dijVert

    Vertex<LabelType>* currentVertex;
    int numNeighbors = 0;
    Vertex<LabelType>* neighborVertex;

    DijkstraVertex* neighborDij;
    DijkstraVertex* currentDij;

    int j = 0;
    while(finishedVertices.size() <= unfinishedVertices.size()) {

        currentVertex = this->vertices.getItem(finishedVertices.back()->getLabel());

        numNeighbors = currentVertex->getNumberOfNeighbors();
        currentVertex->resetNeighbor();

        // cout << currentVertex->getLabel() << endl;
        for(int i = 0; i < numNeighbors; i++) {
            neighborVertex = this->vertices.getItem(currentVertex->getNextNeighbor());

            // find dijVertex that = neighborVertex
			neighborDij = 0;
            for(unsigned k = 0; k < unfinishedVertices.size(); k++)
                if(unfinishedVertices[k]->getLabel() == neighborVertex->getLabel())
                    neighborDij = unfinishedVertices[k];
            currentDij = finishedVertices.back();

            // if distTo dijVertex[current] + edgeWeight(current to neighbor) < dijVertex[neighbor]
            // update dijVertex[neighbor]: prevVertex, and distTo
            if(currentDij->getDist() + currentVertex->getEdgeWeight(neighborVertex->getLabel()) < neighborDij->getDist()) {
                neighborDij->setDist(currentDij->getDist() + currentVertex->getEdgeWeight(neighborVertex->getLabel()));
                neighborDij->setPrev(currentDij);
            }

            // cout << neighborVertex->getLabel() << " ";
            // cout << neighborDij->getDist() << ": from " << neighborDij->getPrev()->getLabel() << endl;
        }
        // cout << endl << endl;

        // then push_back to finishedVertices
        finishedVertices.push_back(unfinishedVertices[j++]);
    }

    startPoint->setDist(0);
    startPoint->setPrev(startPoint);

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

    return LinkedGraph<LabelType>::remove(start, end);
}

template <class LabelType>
bool Dijkstra<LabelType>::setStartPoint(LabelType startP)
{
    if(!this->vertices.contains(startP))
        return false;
	delete startPoint;
    startPoint = new DijkstraVertex(startP); // posibly change this to delete previous startPoint or, 
											 // not use new but point to another existing value
    return false;
}

template <class LabelType>
bool Dijkstra<LabelType>::setEndPoint(LabelType endP)
{
    if(!this->vertices.contains(endP)) {
        return false;
    }
    endPoint = endP;
    return true;
}

template <class LabelType>
int Dijkstra<LabelType>::distanceTo(LabelType x)
{
    applyDijkstra();
    for(unsigned i = 0; i < finishedVertices.size(); i++) {
        if(finishedVertices[i]->getLabel() == x) {
            return finishedVertices[i]->getDist();
        }
    }
    // not found
    return -1;
}

template <class LabelType>
void Dijkstra<LabelType>::writeToFile(ofstream& fout) const
{
    // Write the path taken to endPoint, use finished vertices, following prevVertex


    fout << "Dijkstra write to file. " << endl;
}






