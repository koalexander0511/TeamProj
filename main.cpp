// CIS 22C Team 4 Project: Dijkstra's algorithm (shortest path)
// Program Edited by Ko Outlaw-Spruell, James Hinds, and Victoriia Petrusha


#include <iostream>
#include <string>
#include <cstdlib>
#include "LinkedGraph.h"
#include "Dijkstra.h"
#include "Airport.h"

using namespace std;

typedef Dijkstra<Airport> *T;

void displayMenu();
void createGraph(T &t);
void displayAirport(Airport& port);

int main()
{
   T g1 = new Dijkstra<Airport>();
   bool done = false;
   int choice;
   string sCity, eCity;
   string sAirport, eAirport;
   int weight;
   Airport tempAirport1;
   Airport tempAirport2;

   T airport1, airport2;
   string tempPort, tempCity;
   int dist;

   fstream fin;
   fin.open(INPUTFILE);

   Dijkstra* Flights;
   while(fin >> tempPort)
   {
   		fin >> tempCity;
		airport1 = new Airport(tempPort, tempCity);
		fin >> tempPort;
		fin >> tempCity;
		airport2 = new Airport(tempPort,tempCity);
		fin >> dist;
		Flights->add(airport1,airport2,dist);
   }

   createGraphFromFile(fin); //create a graph from input file

	do {
		displayMenu();
		cin >> choice;

		switch (choice)
		{
		case 1: //display help menu
			displayMenu();
			break;

		case 2: //add an edge, 2 vertices
			cout << "Enter the start vertex(airport city): ";
			cin >> sAirport >> sCity;
			cout << "Enter the end vertex(airport city): ";
			cin >> eAirport >> eCity;
			cout << "Enter the first weight: ";
			cin >> weight;

			tempAirport1.setAirport(sAirport);
			tempAirport1.setCity(sCity);
			tempAirport2.setAirport(eAirport);
			tempAirport2.setCity(eCity);

			g1->add(tempAirport1, tempAirport2, weight);
			break;
		case 3: //display the graph depth traversal
			g1->depthFirstTraversal();
			break;
		case 4: //display the graph breadth traversal
			g1->breadthFirstTraversal();
			break;
		case 5: //remove an edge
			cout << "Enter the start vertex(airport city): ";
			cin >> sAirport >> sCity;
			cout << "Enter the end vertex(airport city): ";
			cin >> eAirport >> eCity;
			tempAirport1.setAirport(sAirport);
			tempAirport1.setCity(sCity);
			tempAirport2.setAirport(eAirport);
			tempAirport2.setCity(eCity);
			g1->remove(tempAirport1, tempAirport2);
			break;
		case 6: //get the number of vertices
			cout << "The number of vertices in the graph = " << g1->GetSize() << endl; // ???????
			break;
		case 7: //search for a certain vertex
		{
					 cout << "Enter a vertex: ";
					 cin >> sname;
					 int result = g1->Search(sname);
					 if (result == -1)
						 cout << "Vertex " << sname << " does not exist in the graph";
					 else
						 cout << "Vertex " << sname << " found in the graph";
					 cout << endl;
					 break;
		}


		case 8: //find the shorted path between two vertices
		{
					 cout << "Enter the starting vertex: ";
					 cin >> vname;
					 cout << "Enter the ending vertex: ";
					 cin >> vname2;
					 int result1 = g1->Search(vname);
					 int result2 = g1->Search(vname2);
					 if (result1 == -1 || result2 == -1){
						 cout << "Error: Invalid vertices" << endl;
					 }
					 else{
						 g1->FindShortestPath(vname, vname2);
					 }
					 break;
		}

		case 9: // undo

			break;

		case 10: // write to file
			cout << "Enter the file name: ";
			cin >> fName;
			writeToFile(fName, g1);
			break;

		case 11: //exit testing
			done = true;
			break;

		default:
			cout << "Invalid choice\n";
			break;
		} //end of switch


	} while (!done);

	cout << "Done with testing!" << endl;
	cin.get();
	cin.get();

	delete g1;
	return 0;
}

// display menu
void displayMenu()
{

	int order = 0;

	cout << order++ << ": Show the menu." << endl;
	cout << order++ << ": Add to Graph." << endl;
	cout << order++ << ": Display vertices." << endl;
	cout << order++ << ": Display the graph." << endl;
	cout << order++ << ": Remove from graph." << endl;
	cout << order++ << ": Get the number of vertices in the graph." << endl;
	cout << order++ << ": Search for a certain vertex." << endl;
	cout << order++ << ": Find the shortest path between two vertices." << endl;
	cout << order++ << ": Undo last chnge." << endl;
	cout << order++ << ": Write graph to file." << endl;
	cout << 11 << ": Exit the program." << endl << endl;

}
void displayAirport(Airport& port)
{
	cout << port;
}
