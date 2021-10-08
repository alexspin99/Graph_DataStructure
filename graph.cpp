#include "graph.h"

using namespace std;

Graph::Graph()
{
	vertices = NULL;
}

Graph::~Graph()
{
	VertexNode* vertexDelete;
	EdgeNode* edgeDelete;
	
	//delete ptrs
	while(vertices != NULL)
	{
		vertexDelete = vertices;
		vertices = vertices->nextVertex;
		
		while (vertexDelete->edgePtr != NULL)
		{
			edgeDelete = vertexDelete->edgePtr;
			vertexDelete->edgePtr = edgeDelete->nextEdge;
			delete edgeDelete;
		}
		
		delete vertexDelete;
	}
	
	//set to null
	vertices = NULL;
}

void Graph::AddVertex(string v)
{
	//create new vertex node
	VertexNode* newVertex = new VertexNode;
	newVertex->vname = v;
	newVertex->mark = false;
	newVertex->edgePtr = NULL;
	newVertex->nextVertex = NULL;
	
	//if empty set root vertex
	if (vertices == NULL)
	{
		vertices = newVertex;
		return;
	}
	
	//link to previous vertex if not empty
	VertexNode* previousVertex = vertices;
	while (previousVertex->nextVertex != NULL)
	{
		previousVertex = previousVertex->nextVertex;
	}
	previousVertex->nextVertex = newVertex;
	
	
	
}

void Graph::AddEdge(string s, string d, int w)
{
	//create new edge node
	EdgeNode* newEdge;
	try
	{
		newEdge = new EdgeNode;
		VertexNode* source = VertexExists(s);
		VertexNode* destination = VertexExists(d);
		
		newEdge->weight = w;
		newEdge->destination = destination;
		newEdge->nextEdge = source->edgePtr;
		source->edgePtr = newEdge;
	}
	catch (std::bad_alloc)
	{
		throw GraphFull();
	}
		
}

VertexNode* Graph::VertexExists(string v) const
{
	//searches for vertex with string v
	VertexNode* vertex = vertices;
	
	while (vertex != NULL)
	{
		if (vertex->vname == v)
			return vertex;
		else
			vertex = vertex->nextVertex;
	}
	
	return NULL;
	
}

EdgeNode* Graph::EdgeExists(string s, string d) const
{
	//find source vertex
	VertexNode* source = VertexExists(s);
	
	if (source == NULL)
		throw GraphVertexNotFound();
	
	//searches for edge
	EdgeNode* edge = source->edgePtr;
	
	while (edge != NULL)
	{
		if (edge->destination->vname == d)
			return edge;
		else 
			edge = edge->nextEdge;
	}
	
	return NULL;
}

int Graph::WeightIs(string s, string d)
{
	//searches for edge
	EdgeNode* edge = EdgeExists(s,d);
	
	if(edge == NULL)
		throw GraphEdgeNotFound();	
	else 
		return edge->weight;
	
}

void Graph::ClearMarks()
{
	VertexNode* vertex = vertices;
	
	//clears mark for all vertices
	for( ; vertex != NULL ; vertex = vertex->nextVertex)
		vertex->mark = false;
		
		
}

void Graph::MarkVertex(string v)
{
	VertexNode* vertex = VertexExists(v);
	if (vertex == NULL)
		throw GraphVertexNotFound();
	vertex->mark = true;
}

bool Graph::IsMarked(string v)
{
	VertexNode* vertex = VertexExists(v);
	if (vertex == NULL)
		throw GraphVertexNotFound();
	
	return vertex->mark;
}

void Graph::GetToVertices(string v, queue<string>& q)
{
	VertexNode* vertex = VertexExists(v);
	if (vertex == NULL)
		throw GraphVertexNotFound();
	
	EdgeNode* edge = vertex->edgePtr;
	
	if (edge == NULL)
		return;
	
	for ( ; edge != NULL ; edge = edge->nextEdge)
		q.push(edge->destination->vname);

}

//searches by levels
void Graph::DepthFirstSearch(string startVertex, string endVertex, queue<string>& path)
{
	ClearMarks();
	
	if ( (VertexExists(startVertex) == NULL) || (VertexExists(endVertex) == NULL) )
		throw GraphVertexNotFound();
	
	//creates queue and stack
	queue<string> adjacent;
	stack<string> stack;
	
	stack.push(startVertex);
	
	while (!stack.empty())
    {
        // Adds top vertex in stack to path queue if it isn't marked
        if (!IsMarked(stack.top()))
        {
            path.push(stack.top());
            MarkVertex(stack.top());
        }
		
		if(stack.top() == endVertex)
			return;
		
		//pops top item from stack
		stack.pop();
		
        // Checks adjacent vertices 
        GetToVertices(path.back(), adjacent);
		while (!adjacent.empty())
		{
			//check if front item is marked
			if (IsMarked(adjacent.front()))
			{
				adjacent.pop();
			}
			else
			{
				stack.push(adjacent.front());
				adjacent.pop();
			}
			
		}
	}
	
	while (!path.empty())
	{
		path.pop();
	}
	
	
}

//searches by taking a path until a dead end is reached, then it backtracksto unmarked adjacent vertices
void Graph::BreadthFirstSearch(string startVertex, string endVertex, queue<string>& visitedq)
{
	queue<string> q;
	queue<string> adjQ;

	if ( (VertexExists(startVertex) == NULL) || (VertexExists(endVertex) == NULL) )
		throw GraphVertexNotFound();
	
	bool found = false;
	string vertex;
	string item;

	ClearMarks();
	q.push(startVertex);
	do
	{
		vertex = q.front();
		q.pop();
		if (vertex == endVertex)
		{
			found = true;
			visitedq.push(vertex);
		}
		else
		{
			if (!IsMarked(vertex))
			{
				MarkVertex(vertex);
				visitedq.push(vertex);
				GetToVertices(vertex, adjQ);

				while (! adjQ.empty() )
				{
					item = adjQ.front();
					adjQ.pop();

					if (!IsMarked(item))
						q.push(item);
				}
			}
		}
	} while (!q.empty() && !found);

	if (!found)
	{
		while (!visitedq.empty())
		{
			visitedq.pop();
		}
	} 
	
}







