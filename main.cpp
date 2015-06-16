//Test

/*
    CIS 22C Team 4 Project: Dijkstra's algorithm (shortest path)

    12 June 2015
*/

//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//
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
void display(string& anItem)
{
   cout << "Displaying item - " << anItem << endl;
}
int main()
{

   //LinkedGraph<string>* myGraph = new LinkedGraph<string>();

   cout << "Testing Graph . . . ." << endl << endl ;
   //graphTest(myGraph);
   T g1;
   bool done = false;
   int choice;
   T sname, ename;
   T weight;

   /*
   PSUDOCODE FOR CREATING A GRAPH FROM INPUT FILE.

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
   */

   createGraph(g1); //create a graph from input file

	do {
		displayMenu();
		cin >> choice;

		switch (choice)
		{
		case 1: //display help menu
			displayMenu();
			break;

		case 2: //add a vertex
			cout << "Enter the start vertex: ";
			cin >> sname;
			cout << "Enter the end vertex: ";
			cin >> ename;
			cout << "Enter the weight: ";
			cin >> weight;
			g1.add(sname, ename, weight);
			break;
		case 3: //display vertices in the graph
			g1.DisplayVertices();
			break;
		case 4: //display the graph
			g1.DisplayGraph();
			break;
		case 5: //remove an edge
			cout << "Enter the starting vertex: ";
			cin >> sname;
			cout << "Enter the ending vertex: ";
			cin >> ename;
			g1.remove(sname, ename);
			break;
		case 6: //get the number of vertices
			cout << "The number of vertices in the graph = " << g1.GetSize() << endl; // ???????
			break;
		case 7: //search for a certain vertex
		{
					 cout << "Enter a vertex: ";
					 cin >> sname;
					 int result = g1.Search(sname);
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
					 int result1 = g1.Search(vname);
					 int result2 = g1.Search(vname2);
					 if (result1 == -1 || result2 == -1){
						 cout << "Error: Invalid vertices" << endl;
					 }
					 else{
						 g1.FindShortestPath(vname, vname2);
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
/*
 Testing Graph . . . .

 Vertices :14
 Edges :14

 Depth-first traversal (should be A B E F J C G K L D H M I N):
 Displaying item - A
 Displaying item - B
 Displaying item - E
 Displaying item - F
 Displaying item - J
 Displaying item - C
 Displaying item - G
 Displaying item - K
 Displaying item - L
 Displaying item - D
 Displaying item - H
 Displaying item - M
 Displaying item - I
 Displaying item - N

 Breadth-first traversal (should be A B C D E F G H I J K L M N):
 Displaying item - A
 Displaying item - B
 Displaying item - C
 Displaying item - D
 Displaying item - E
 Displaying item - F
 Displaying item - G
 Displaying item - H
 Displaying item - I
 Displaying item - J
 Displaying item - K
 Displaying item - L
 Displaying item - M
 Displaying item - N
*/
