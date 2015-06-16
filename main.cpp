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


bool openInputFile(ifstream &ifs) //function that asks the user to enter a file name. Opens the file, and returns true if it worked.
{
	string filename; // temp storage for user input. Stores the name of the file that the user wants to open

	cout << "Enter the input filename: ";
	getline(cin, filename);
	ifs.open(filename.c_str());
	return ifs.is_open();
}
void createGraphFromFile(ifstream &fin, T &map)
{
	Airport *airport1, *airport2;
	string tempPort, tempCity;
	int dist;

	while (fin >> tempPort)
	{
		fin >> tempCity;
		airport1 = new Airport(tempPort, tempCity);
		fin >> tempPort;
		fin >> tempCity;
		airport2 = new Airport(tempPort, tempCity);
		fin >> dist;
		map->add(*airport1, *airport2, dist);
	}
}
int main()
{

   //LinkedGraph<string>* myGraph = new LinkedGraph<string>();

   cout << "Testing Graph . . . ." << endl << endl ;
   //graphTest(myGraph);
   T g1 = new Dijkstra<Airport>();
   bool done = false;
   int choice;
   string sCity, eCity;
   string sAirport, eAirport;
   int weight;

   Airport tempAirport1;
   Airport tempAirport2;

   ifstream fin;
   while(openInputFile(fin));
   createGraphFromFile(fin, g1);

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
		    // Enter starting point for traversal
		    cout << "Enter the start vertex(airport city): ";
			cin >> sAirport >> sCity;
			tempAirport1.setAirport(sAirport);
			tempAirport1.setCity(sCity);

			g1->depthFirstTraversal(tempAirport1, displayAirport);
			break;
		case 4: //display the graph breadth traversal
		    // Enter starting point for traversal
		    cout << "Enter the start vertex(airport city): ";
			cin >> sAirport >> sCity;
			tempAirport1.setAirport(sAirport);
			tempAirport1.setCity(sCity);

			g1->breadthFirstTraversal(tempAirport1, displayAirport);
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
			cout << "The number of vertices in the graph = " << g1->getNumVertices() << endl;
			break;
		case 7: //search for a certain vertex
		{
					 cout << "Enter a vertex(airport city): ";
					 cin >> sAirport >> sCity;
					 tempAirport1.setAirport(sAirport);
					 tempAirport1.setCity(sCity);

					 int result = g1->searchVertex(tempAirport1);
					 if (result == -1)
						 cout << "Vertex " << tempAirport1 << " does not exist in the graph";
					 else
						 cout << "Vertex " << tempAirport1 << " found in the graph";
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
