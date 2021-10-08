//
// main.cpp  
//
// Driver program for Graph class -- The text files (read by this code) contain a series 
// of commands that will help you test your Graph ADT code by triggering various class methods.
//
// DO NOT MODIFY THIS FILE
//
#include <iostream>
#include <fstream>
#include "graph.h"
#include <stack>				// For STL stack class
#include <queue>				// For STL queue class

using namespace std;

int main(int argc, char* argv[])
{
	ifstream inputs;			// Input file for commands
	char op, ch;				// Hold operation and optional char input
	Graph* gPtr = NULL;     // Will point to Graph object
	int num;                // Holds number of graph nodes
	string v1, v2;				// Vertex names input from file
	int w;						// Edge weight input from file
	queue<string> visitedq; // Visited vertices queue
    queue<string> adjq;     // Adjacent vertics queue
	string  comment;        // Comment input from file
	
	// Output usage message if one input file name is not provided
	if (argc != 2)
	{
		cout << "Usage:\n  project06  <inputfile>\n";
		return 1;
	}
	
	// Attempt to open input file -- terminate if file does not open
	inputs.open(argv[1]);
	if (!inputs)
	{
		cout << "Error - unable to open input file" << endl;
		return 1;
	}
	
	cout << endl;
	
	// Process commands from input file
	getline(inputs, comment);
	cout << comment << endl;
	
	inputs >> op;			// Attempt to input number of vertices
	while (inputs)
	{		
		switch (op)
		{
			case '#':   // Comment
				try
                {
                    cout << '#';
                    getline(inputs, comment);
				    cout << comment << endl;
                }
 				catch ( ... )
                {
				   cout << "Error: unanticipated exception" << endl;
                }  
				break;
				
			case 'c':	// Construct empty graph object
				try
                {
                    cout << "Constructor()" << endl;
				    gPtr = new Graph();
                }
 				catch ( ... )
                {
				   cout << "Error: unanticipated exception" << endl;
                }  
				break;
				
			case 'v':	// Add vertex to graph object
				try
                {
                    inputs >> v1;
				    cout << "AddVertex(" << v1 << ")" << endl;
				    gPtr->AddVertex(v1);
                }
                catch ( std::bad_alloc )
                {
                    cout << "Error - full: unable to add vertex" << endl;
                }
 				catch ( ... )
                {
				   cout << "Error: unanticipated exception in AddVertex" << endl;
                }           
				break;
				
			case 'd':	// Add directed edge to graph object
				try
                {
                    inputs >> v1 >> v2 >> w;
				    cout << "AddEdge(" << v1 << ", " << v2 << ", " << w << ")" << endl;
				    gPtr->AddEdge(v1, v2, w);
                }
                catch ( std::bad_alloc )
                {
                    cout << "Error - full: unable to add directed" << endl;
                }
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in AddEdge" << endl;
                }
				break;
				
			case 'u':	// Add undirected edge to graph object
				try
                {
				    inputs >> v1 >> v2 >> w;
				    cout << "AddEdge(" << v1 << ", " << v2 << ", " << w << ")" << endl;
				    gPtr->AddEdge(v1, v2, w);
				    cout << "AddEdge(" << v2 << ", " << v1 << ", " << w << ")" << endl;
				    gPtr->AddEdge(v2, v1, w);
                }
                catch ( std::bad_alloc )
                {
                    cout << "Error - full: unable to add undirected edge" << endl;
                }
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in AddEdge" << endl;
                }
				break;
				
			case '?':	// VertexExists()
                try
                {
				    inputs >> v1;
				    if (gPtr->VertexExists(v1) != NULL)
					    cout << "VertexExists(" << v1 << ") -- true" << endl;
				    else
					    cout << "VertexExists(" << v1 << ") -- false" << endl;
                }
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in VertexExists" << endl;
                }
				break;

			case '!':	// EdgeExists()
                try
                {
                    inputs >> v1 >> v2;
				    if (gPtr->EdgeExists(v1, v2) != NULL)
					    cout << "EdgeExists(" << v1 << ", " << v2 << ") -- true" << endl;
				    else
					    cout << "EdgeExists(" << v1 << ", " << v2 << ") -- false" << endl;
                }
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in EdgeExists" << endl;
                }
				break;	
			
			case 'w':	// WeightIs()
				try
				{
                    inputs >> v1 >> v2;
					cout << "WeightIs(" << v1 << ", " << v2 << ") -- ";
					w = gPtr->WeightIs(v1, v2);
					cout << w << endl;
				}
				catch ( GraphVertexNotFound )
				{
				    cout << "Error: vertex not found" << endl;
				}
				catch ( GraphEdgeNotFound )
				{
					cout << "Error: edge not found" << endl;
				}
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in WeightIs" << endl;
                }
				break;

			case 'm':	// MarkVertex()
				try
				{
                    inputs >> v1;
					cout << "MarkVertex(" << v1 << ") ";
					gPtr->MarkVertex(v1);
					cout << endl;
				}
				catch ( GraphVertexNotFound )
				{
				    cout << "Error: vertex not found" << endl;
				}
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in MarkVertex" << endl;
                }
				break;

			case 'e':	// ClearMarks()
				try
				{
					cout << "ClearMarks() ";
					gPtr->ClearMarks();
					cout << endl;
				}
				catch ( GraphVertexNotFound )
				{
				   cout << "Error: vertex not found" << endl;
				}
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in ClearMarks" << endl;
                }
				break;

			case 'i':	// IsMarked()
				try
				{
                    inputs >> v1;
					cout << "IsMarked(" << v1 << ") -- ";
					if (gPtr->IsMarked(v1))
                        cout << "true";
                    else
                        cout << "false";
					cout << endl;
				}
				catch ( GraphVertexNotFound )
				{
				   cout << "Error: vertex not found" << endl;
				}
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in IsMarked" << endl;
                }
				break;
				
			case 's':	// Perform Depth-First Search
				try
				{
				    inputs >> v1 >> v2;		// Input v1-start and v2-end vertices
				
				    cout << "DFS( " << v1 << ", " << v2 << " ) -- ";
					gPtr->DepthFirstSearch(v1, v2, visitedq);

					if (visitedq.empty())
						cout << "No path found" << endl;
					else
					{
						cout << " { ";
						while (!visitedq.empty())
						{
							cout << visitedq.front() << " ";
							visitedq.pop();
						}
						cout << "}" << endl;
					}
				}
				catch ( GraphVertexNotFound )
				{
				    cout << "Error: vertex not found" << endl;
				}
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in DFS" << endl;
                }				
				while (!visitedq.empty())
					visitedq.pop();
				break;

			case 'g':	// GetToVertices
				try
				{
				    inputs >> v1;		
				
				    cout << "GetToVertices( " << v1 << " ) -- ";
					gPtr->GetToVertices(v1, adjq);

					if (adjq.empty())
						cout << "No adjacent vertices found" << endl;
					else
					{
						cout << " { ";
						while (!adjq.empty())
						{
							cout << adjq.front() << " ";
							adjq.pop();
						}
						cout << "}" << endl;
					}
				}
				catch ( GraphVertexNotFound )
				{
				    cout << "Error: vertex not found" << endl;
				}
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in GetToVertices" << endl;
                }				
				while (!adjq.empty())
					adjq.pop();
				break;
		

			case 'b':	// Perform Breadth-First Search
				try
				{
				    inputs >> v1 >> v2;		// Input v1-start and v2-end vertices
				
				    cout << "BFS( " << v1 << ", " << v2 << " ) -- ";
					gPtr->BreadthFirstSearch(v1, v2, visitedq);

					if (visitedq.empty())
						cout << "No path found" << endl;
					else
					{
						cout << " { ";
						while (!visitedq.empty())
						{
							cout << visitedq.front() << " ";
							visitedq.pop();
						}
						cout << "}" << endl;
					}
				}
				catch ( GraphVertexNotFound )
				{
				    cout << "Error: vertex not found" << endl;
				}
				catch ( ... )
                {
				    cout << "Error: unanticipated exception in BFS" << endl;
                }				
				while (!visitedq.empty())
					visitedq.pop();
				break;
				
			case 'p':	// Print Graph
				gPtr->Print();
				break;
				
			case '~':	// Destructor
				try
                {
                    delete gPtr;
				    gPtr = NULL;
				    cout << "Destructor()" << endl << endl;
                }
 				catch ( ... )
                {
				    cout << "Error: unanticipated exception" << endl;
                }  
				break;
				
			default:	// Error
				cout << "Error - unrecognized operation '" << op << "'" << endl;
				cout << "Terminating now..." << endl;
				return 1;
				break;
		}
		
		inputs >> op;	// Attempt to input next command
	}
	
	
  return 0;
}






