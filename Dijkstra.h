
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
		bool isFinished;
	public:
		DijkstraVertex() : label(), distTo(INT_MAX), isFinished(false) {}
		DijkstraVertex(LabelType l) : label(l), distTo(INT_MAX), isFinished(false) {}

		void setDist(int d) { distTo = d; }
		void setPrev(LabelType pl) { prevLabel = pl; }
		void setFinished(bool f) { isFinished = f; }
		int getDist() const { return distTo; }
		LabelType getPrev() const { return prevLabel; }
		LabelType getLabel() const { return label; }
		DijkstraVertex& operator=(const DijkstraVertex& right) 
		{
			label = right.label; setDist(right.distTo); setPrev(right.prevLabel); return *this; 
		}
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

	void writeToFile(ofstream&);
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
	int startIndex = 0;
	for (unsigned i = 0; i < unfinishedVertices.size(); i++) {
		unfinishedVertices[i].setDist(INT_MAX);
		unfinishedVertices[i].setPrev(unfinishedVertices[i].getLabel());
		if (unfinishedVertices[i].getLabel() == startPoint) {
			startIndex = i;
		}
	}
	// move startPoint to index 0
	DijkstraVertex tempDij = unfinishedVertices[0];
	unfinishedVertices[0] = unfinishedVertices[startIndex];
	unfinishedVertices[startIndex] = tempDij;

	// set startPoint distance
	unfinishedVertices[0].setDist(0);
	unfinishedVertices[0].setPrev(unfinishedVertices[0].getLabel());

	finishedVertices.clear();

	finishedVertices.push_back(unfinishedVertices[0]);

	while (finishedVertices.size() < unfinishedVertices.size()) {
		// number of neighbors at the current vertex
		Vertex<LabelType>* currentVertex = vertices.getItem(finishedVertices.back().getLabel());
		int numNeighbors = currentVertex->getNumberOfNeighbors();
		currentVertex->resetNeighbor();

		// relax each neighbor
		for (int k = 0; k < numNeighbors; k++) {
			LabelType neighbor = currentVertex->getNextNeighbor();

			// get neighbor unfinishedVertices index
			unsigned neighborIndex = 0;
			for (unsigned l = 0; l < unfinishedVertices.size(); l++) {
				if (unfinishedVertices[l].getLabel() == neighbor){
					neighborIndex = l;
					break;
				}
			}

			if (finishedVertices.back().getDist() + getEdgeWeight(finishedVertices.back().getLabel(), neighbor) < 
				unfinishedVertices[neighborIndex].getDist()) {
				// found improved route
				unfinishedVertices[neighborIndex].setDist(finishedVertices.back().getDist() + getEdgeWeight(finishedVertices.back().getLabel(), neighbor));
				unfinishedVertices[neighborIndex].setPrev(finishedVertices.back().getLabel());
			}
		}

		// iterate through neighbors again, and push_back() to finishedVertices one that is not already in finishedVertices
		currentVertex->resetNeighbor();
		for (int k = 0; k < numNeighbors; k++) {
			LabelType neighbor = currentVertex->getNextNeighbor();
			// get neighbor unfinishedVertices index
			unsigned neighborIndex = 0;
			for (unsigned l = 0; l < unfinishedVertices.size(); l++) {
				if (unfinishedVertices[l].getLabel() == neighbor){
					neighborIndex = l;
					break;
				}
			}
			// check if that neighbor has already been added
			bool added = false;
			for (unsigned l = 0; l < finishedVertices.size(); l++) {
				if (finishedVertices[l].getLabel() == unfinishedVertices[neighborIndex].getLabel()) {
					added = true;
					break;
				}
			}
			if (added) {
				continue;
			}
			else {
				// push_back neighbor that is not already in finishedVertices
				finishedVertices.push_back(unfinishedVertices[neighborIndex]);
				break;
			}
		}
	}	

	return true;
}

template <class LabelType>
bool Dijkstra<LabelType>::add(LabelType start, LabelType end, int edgeWeight)
{
	if (!this->vertices.contains(start))
		unfinishedVertices.push_back(DijkstraVertex(start));
	if (!this->vertices.contains(end))
		unfinishedVertices.push_back(DijkstraVertex(end));

	return LinkedGraph<LabelType>::add(start, end, edgeWeight);
}

template <class LabelType>
bool Dijkstra<LabelType>::remove(LabelType start, LabelType end)
{

	bool isRemoved = LinkedGraph<LabelType>::remove(start, end);
	if (!searchVertex(start)) {
		// remove from unfinishedVertices
		for (unsigned i = 0; i < unfinishedVertices.size(); i++) {
			if (unfinishedVertices[i].getLabel() == start) {
				unfinishedVertices.erase(unfinishedVertices.begin() + i);
				break;
			}
		}
	}
	if (!searchVertex(end)) {
		// remove from unfinishedVertices
		for (unsigned i = 0; i < unfinishedVertices.size(); i++) {
			if (unfinishedVertices[i].getLabel() == end) {
				unfinishedVertices.erase(unfinishedVertices.begin() + i);
				break;
			}
		}
	}

	return isRemoved;
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

	for (unsigned i = 0; i < finishedVertices.size(); i++) {
		if (finishedVertices[i].getLabel() == x) {
			return finishedVertices[i].getDist();
		}
	}
	// not found
	cout << "not found" << endl;
	return -1;
}

template <class LabelType>
void Dijkstra<LabelType>::writeToFile(ofstream& fout)
{
	applyDijkstra();

	fout << "Path from " << startPoint << " to " << endPoint << ": " << endl;

	vector<LabelType> path;

	// assign tempDij to endPoint
	DijkstraVertex tempDij;
	for (unsigned i = 0; i < finishedVertices.size(); i++) {
		if (finishedVertices[i].getLabel() == endPoint) {
			tempDij = finishedVertices[i];
			fout << "Distance to " << tempDij.getLabel() << ": " << tempDij.getDist() << endl;
			break;
		}
	}

	// write path taken to endPoint, following prevVertex
	do {
		path.push_back(tempDij.getLabel());
		LabelType tempLabel = tempDij.getPrev();

		// set tempDij to previous
		for (unsigned i = 0; i < finishedVertices.size(); i++) {
			if (finishedVertices[i].getLabel() == tempLabel) {
				tempDij = finishedVertices[i];
				break;
			}
		}
	} while (!(tempDij.getLabel() == startPoint));
	
	fout << "1. " << startPoint << endl;
	for (unsigned i = 0; i < path.size(); i++) {
		fout << i+2 << ". " << path[path.size()-1-i] << endl;
	}
}






