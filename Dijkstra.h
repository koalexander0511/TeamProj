
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
private:
    Vertex<LabelType> startPoint;
    Vertex<LabelType> endPoint;
    vector<int> dist;
    vector<Vertex<LabelType> > finishedVertecies;
    vector<Vertex<LabelType> > unfinishedVertices;

    bool applyDijkstra();
public:
    Dijkstra();
    Dijkstra(const Dijkstra<LabelType>&);
    ~Dijkstra();

    bool setStartPoint(LabelType);
    bool setEndPoint(LabelType);
    void writeToFile(ofstream&);
};
