
/*
CIS 22C Team 4 Project: Dijkstra's algorithm (shortest path)
Program Edited by Ko Outlaw-Spruell, James Hinds, and Victoriia Petrusha

18 June 2015
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
// #include <crtdbg.h>
#include "Dijkstra.h"
#include "Airport.h"

using namespace std;

void displayMenu();
void displayAirport(Airport& port);

bool openInputFile(ifstream &ifs) //function that asks the user to enter a file name. Opens the file, and returns true if it worked.
{
	string filename; // temp storage for user input. Stores the name of the file that the user wants to open

	cout << "Enter the input filename: ";
	getline(cin, filename);
	ifs.open(filename.c_str());
	return ifs.is_open();
}

bool openOutputFile(ofstream &fout) //function that asks the user to enter a file name. Opens the file, and returns true if it worked.
{
	string filename; // temp storage for user input. Stores the name of the file that the user wants to open

	cout << "Enter the output filename: ";
	getline(cin, filename);
	fout.open(filename.c_str());
	return fout.is_open();
}

void createGraphFromFile(ifstream &fin, Dijkstra<Airport>* g)
{
	Airport airport1, airport2;
	string tempPort, tempCity;
	int dist;

	while (fin >> tempPort)
	{
		fin >> tempCity;
		airport1.setAirport(tempPort);
		airport1.setCity(tempCity);
		fin >> tempPort;
		fin >> tempCity;
		airport2.setAirport(tempPort);
		airport2.setCity(tempCity);
		fin >> dist;
		g->add(airport1, airport2, dist);
	}
}

int main()
{
	{
		Dijkstra<Airport>* g1 = new Dijkstra<Airport>();

		bool done = false;
		int choice;

		string sCity, eCity;
		string sAirport, eAirport;
		int weight = 0;

		Airport tempAirport1;
		Airport tempAirport2;

		ofstream fout;
		ifstream fin;

		do {
			displayMenu();

			// user chooses menu item
			while (!(cin >> choice)) {
				cout << "Please enter a number. " << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cin.ignore(1000, '\n');

			switch (choice)
			{
			case 1: // read in from file
			{
				while (!openInputFile(fin));
				createGraphFromFile(fin, g1);
				fin.close();
				break;
			}

			case 2: // add an edge, 2 vertices
			{
				cout << "Enter the starting Airport(3 capital letters): ";
				getline(cin, sAirport);
				cout << "Enter the starting City: ";
				getline(cin, sCity);

				cout << "Enter the ending Airport(3 capital letters): ";
				getline(cin, eAirport);
				cout << "Enter the ending City: ";
				getline(cin, eCity);

				cout << "Enter the weight: ";
				cin >> weight;

				tempAirport1.setAirport(sAirport);
				tempAirport1.setCity(sCity);
				tempAirport2.setAirport(eAirport);
				tempAirport2.setCity(eCity);

				g1->add(tempAirport1, tempAirport2, weight);
				break;
			}

			case 3: //display the graph depth traversal
			{
				// Enter starting point for traversal
				cout << "Enter the starting Airport(3 capital letters): ";
				getline(cin, sAirport);
				cout << "Enter the starting City: ";
				getline(cin, sCity);

				tempAirport1.setAirport(sAirport);
				tempAirport1.setCity(sCity);

				// check if vertex is valid
				if (!g1->searchVertex(tempAirport1)) {
					cout << "Vertex " << tempAirport1 << " does not exist in the graph" << endl;
					break;
				}

				// preform traversal
				cout << endl;
				g1->depthFirstTraversal(tempAirport1, displayAirport);
				cout << endl;
				break;
			}

			case 4: //display the graph breadth traversal
			{
				// Enter starting point for traversal
				cout << "Enter the starting Airport(3 capital letters): ";
				getline(cin, sAirport);
				cout << "Enter the starting City: ";
				getline(cin, sCity);
				tempAirport1.setAirport(sAirport);
				tempAirport1.setCity(sCity);

				// check if vertex is valid
				if (!g1->searchVertex(tempAirport1)) {
					cout << "Vertex " << tempAirport1 << " does not exist in the graph" << endl;
					break;
				}

				// preform traversal
				cout << endl;
				g1->breadthFirstTraversal(tempAirport1, displayAirport);
				cout << endl;
				break;
			}

			case 5: //remove an edge
			{
				cout << "Enter the starting Airport(3 capital letters): ";
				getline(cin, sAirport);
				cout << "Enter the starting City: ";
				getline(cin, sCity);

				cout << "Enter the ending Airport(3 capital letters): ";
				getline(cin, eAirport);
				cout << "Enter the ending city: ";
				getline(cin, eCity);

				tempAirport1.setAirport(sAirport);
				tempAirport1.setCity(sCity);
				tempAirport2.setAirport(eAirport);
				tempAirport2.setCity(eCity);

				// check if vertex is valid
				if (!g1->searchVertex(tempAirport1)) {
					cout << "Vertex " << tempAirport1 << " does not exist in the graph" << endl;
					break;
				}

				// check if vertex is valid
				if (!g1->searchVertex(tempAirport2)) {
					cout << "Vertex " << tempAirport2 << " does not exist in the graph" << endl;
					break;
				}

				// preform removal
				g1->remove(tempAirport1, tempAirport2);
				break;
			}

			case 6: //get the number of vertices
			{
				cout << "The number of vertices in the graph = " << g1->getNumVertices() << endl;
				break;
			}

			case 7: //search for a certain vertex
			{
				cout << "Enter an Airport(3 capital letters): ";
				getline(cin, sAirport);
				cout << "Enter a City: ";
				getline(cin, sCity);

				tempAirport1.setAirport(sAirport);
				tempAirport1.setCity(sCity);

				if (!g1->searchVertex(tempAirport1))
					cout << "Vertex " << tempAirport1 << " does not exist in the graph";
				else
					cout << "Vertex " << tempAirport1 << " found in the graph";
				cout << endl;
				break;
			}

			case 8: //find the shorted path between two vertices
			{
				cout << "Enter the starting Airport(3 capital letters): ";
				getline(cin, sAirport);
				cout << "Enter the starting City: ";
				getline(cin, sCity);

				cout << "Enter the ending Airport(3 capital letters): ";
				getline(cin, eAirport);
				cout << "Enter the ending city: ";
				getline(cin, eCity);

				tempAirport1.setAirport(sAirport);
				tempAirport1.setCity(sCity);
				tempAirport2.setAirport(eAirport);
				tempAirport2.setCity(eCity);
				cout << endl;

				bool result1 = g1->searchVertex(tempAirport1);
				bool result2 = g1->searchVertex(tempAirport2);
				if (!result1 || !result2) {
					cout << "Error: Invalid vertices" << endl;
				}
				else{
					g1->setStartPoint(tempAirport1);
					g1->setEndPoint(tempAirport2);
					int d = g1->distanceTo(tempAirport2);
					cout << "Distance to: " << tempAirport2 << " = " << d << endl;
				}
				break;
			}

			case 9: // undo
			{
				// undo last add or removal
				g1->undo();
				break;
			}

			case 10: // write to file
			{
				while (!openOutputFile(fout));

				cout << "Enter the starting Airport(3 capital letters): ";
				getline(cin, sAirport);
				cout << "Enter the starting City: ";
				getline(cin, sCity);

				cout << "Enter the ending Airport(3 capital letters): ";
				getline(cin, eAirport);
				cout << "Enter the ending city: ";
				getline(cin, eCity);

				tempAirport1.setAirport(sAirport);
				tempAirport1.setCity(sCity);
				tempAirport2.setAirport(eAirport);
				tempAirport2.setCity(eCity);
				cout << endl;

				g1->setStartPoint(tempAirport1);
				g1->setEndPoint(tempAirport2);

				// write distance and shortest path sequence to file
				g1->writeDijkstraToFile(fout);
				fout.close();
				break;
			}

			case 11: //exit testing
			{
				done = true;
				break;
			}

			default:
			{
				cout << "Invalid choice\n";
				break;
			}
			} //end of switch

			cout << endl;
		} while (!done);

		cout << "Program will now exit. " << endl;
		cin.get();

		delete g1;
	}

	// test for memory leaks
	// cout << (_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Leak\n");

	return 0;
} // end main

// display menu
void displayMenu()
{

	int order = 1;

	cout << order++ << ": Read graph from file." << endl;
	cout << order++ << ": Add to graph." << endl;
	cout << order++ << ": Display graph depth traversal." << endl;
	cout << order++ << ": Display graph breadth traversal." << endl;
	cout << order++ << ": Remove from graph." << endl;
	cout << order++ << ": Get the number of vertices in the graph." << endl;
	cout << order++ << ": Search for a certain vertex." << endl;
	cout << order++ << ": Find the shortest distance between two vertices." << endl;
	cout << order++ << ": Undo last change." << endl;
	cout << order++ << ": Write shortest path to file." << endl;
	cout << 11 << ": Exit the program." << endl << endl;

}

void displayAirport(Airport& port)
{
	cout << port << endl;
}

