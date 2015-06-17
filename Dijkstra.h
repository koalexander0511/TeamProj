
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
		LabelType label;
		int distTo; // distance to this vertex
		LabelType prevLabel; // DijkstraVertex that brought you to this one
	public:
		DijkstraVertex() : label(), distTo(INT_MAX) {}
		DijkstraVertex(LabelType l) : label(l), distTo(INT_MAX) {}

		void setDist(int d) { distTo = d; }
		void setPrev(LabelType pl) { prevLabel = pl; }
		int getDist() const { return distTo; }
		LabelType getPrev() const { return prevLabel; }
		LabelType getLabel() const { return label; }
	};

private:
	LabelType startPoint;
	LabelType endPoint;

	vector<DijkstraVertex> finishedVertices; // stored dynamically
	vector<DijkstraVertex> unfinishedVertices; // stored dynamically

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

}

template <class LabelType>
Dijkstra<LabelType>::~Dijkstra()
{
	// delete the contents of unfinishedVertices and finishedVertices
	unfinishedVertices.clear();
	finishedVertices.clear();
}

template <class LabelType>
bool Dijkstra<LabelType>::applyDijkstra()
{
	// unfinished vertices is filled with dij vertices
	// test if need to reset distTo INT_MAX every time, between multiple changes/applyDijkstra's
	for (unsigned i = 0; i < unfinishedVertices.size(); i++) {
		unfinishedVertices[i].setDist(INT_MAX);
	}
	finishedVertices.clear();

	// check if startPoint has been set

	DijkstraVertex sp(startPoint);
	sp.setDist(0);
	finishedVertices.push_back(sp); // start at startPoint, then push back neighbor as dijVert

	Vertex<LabelType>* currentVertex;
	int numNeighbors = 0;
	Vertex<LabelType>* neighborVertex;

	DijkstraVertex neighborDij;
	DijkstraVertex currentDij;

	int j = 0;
	while (finishedVertices.size() <= unfinishedVertices.size()) {

		currentVertex = this->vertices.getItem(finishedVertices.back().getLabel());

		numNeighbors = currentVertex->getNumberOfNeighbors();
		currentVertex->resetNeighbor();

		// cout << currentVertex->getLabel() << endl;
		for (int i = 0; i < numNeighbors; i++) {
			neighborVertex = this->vertices.getItem(currentVertex->getNextNeighbor());

			// find dijVertex that = neighborVertex
			for (unsigned k = 0; k < unfinishedVertices.size(); k++)
				if (unfinishedVertices[k].getLabel() == neighborVertex->getLabel())
					neighborDij = unfinishedVertices[k];
			currentDij = finishedVertices.back();

			// if distTo dijVertex[current] + edgeWeight(current to neighbor) < dijVertex[neighbor]
			// update dijVertex[neighbor]: prevVertex, and distTo
			if (currentDij.getDist() + currentVertex->getEdgeWeight(neighborVertex->getLabel()) < neighborDij.getDist()) {
				neighborDij.setDist(currentDij.getDist() + currentVertex->getEdgeWeight(neighborVertex->getLabel()));
				neighborDij.setPrev(currentDij.getLabel());
			}

			// cout << neighborVertex->getLabel() << " ";
			// cout << neighborDij.getDist() << ": from " << neighborDij.getPrev() << endl;

			for (unsigned l = 0; l < unfinishedVertices.size(); l++) {
				if (unfinishedVertices[l].getLabel() == currentDij.getLabel()) {
					unfinishedVertices[l].setDist(currentDij.getDist());
					unfinishedVertices[l].setPrev(currentDij.getPrev());
				}
			}
			for (unsigned l = 0; l < unfinishedVertices.size(); l++) {
				if (unfinishedVertices[l].getLabel() == neighborDij.getLabel()) {
					unfinishedVertices[l].setDist(neighborDij.getDist());
					unfinishedVertices[l].setPrev(neighborDij.getPrev());
				}
			}
		}
		// cout << endl << endl;

		// then push_back to finishedVertices
		// search for next dijvert that isn't in finished, and distTo < INT_MAX
		DijkstraVertex tempDij = unfinishedVertices[j++];
		bool ftemp = false;
		for (unsigned l = 0; l < unfinishedVertices.size(); l++) {
			if (unfinishedVertices[l].getDist() < INT_MAX) {
				for (unsigned i = 0; i < finishedVertices.size(); i++) {
					if (unfinishedVertices[l].getLabel() == finishedVertices[i].getLabel()) {
						break;
					}
					else {
						tempDij = unfinishedVertices[l];
						ftemp = true;
						break;
					}
				}
			}
			if (ftemp)
				break;
		}
		finishedVertices.push_back(tempDij);
	}

	sp.setDist(0);
	sp.setPrev(sp.getLabel());
	for (unsigned l = 0; l < unfinishedVertices.size(); l++) {
		if (unfinishedVertices[l].getLabel() == sp.getLabel()) {
			unfinishedVertices[l].setDist(sp.getDist());
			unfinishedVertices[l].setPrev(sp.getPrev());
		}
	}

	return true;
}

template <class LabelType>
bool Dijkstra<LabelType>::add(LabelType start, LabelType end, int edgeWeight)
{
	// document change with undoStack, then add() as usual
	// (modify later if Dijkstra::add() requires it)
	if (!this->vertices.contains(start))
		unfinishedVertices.push_back(DijkstraVertex(start));
	if (!this->vertices.contains(end))
		unfinishedVertices.push_back(DijkstraVertex(end));

	return LinkedGraph<LabelType>::add(start, end, edgeWeight);
}

template <class LabelType>
bool Dijkstra<LabelType>::remove(LabelType start, LabelType end)
{
	// document change with undoStack, then add() as usual
	// (change later if Dijkstra::add() requires it)

	// if start or end has no more neighbors due to this remove
	// delete them from unfinished/finished vertices

	return LinkedGraph<LabelType>::remove(start, end);
}

template <class LabelType>
bool Dijkstra<LabelType>::setStartPoint(LabelType startP)
{
	if (!this->vertices.contains(startP))
		return false;
	startPoint = startP; // posibly change this to delete previous startPoint or,
	// not use new but point to another existing value
	return false;
}

template <class LabelType>
bool Dijkstra<LabelType>::setEndPoint(LabelType endP)
{
	if (!this->vertices.contains(endP)) {
		return false;
	}
	endPoint = endP;
	return true;
}

template <class LabelType>
int Dijkstra<LabelType>::distanceTo(LabelType x)
{
	applyDijkstra();
	for (unsigned i = 0; i < unfinishedVertices.size(); i++) {
		if (unfinishedVertices[i].getLabel() == x) {
			return unfinishedVertices[i].getDist();
		}
	}
	// not found
	cout << "not found" << endl;
	return -1;
}

template <class LabelType>
void Dijkstra<LabelType>::writeToFile(ofstream& fout) const
{
	// Write the path taken to endPoint, use finished vertices, following prevVertex


	fout << "Dijkstra write to file. " << endl;
}






