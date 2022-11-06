// graph.cpp

#include <iostream>
#include <sstream>
#include <vector>
#include "vertex.cpp"

using namespace std;

// Graph template class
template <typename D, typename K>
class Graph
{
	private:
    		Vertex<D, K>* *vertices;	// array of vertex pointers
    		int num_of_vertices;	// size of array

    	public:
        	Graph(vector<K> keys, vector<D> data, vector< vector<K> > edges)	// constructor for given keys, data, and adjacency lists of vertices
        	{
        		// if an uneven amount of keys or data or edges are given, no
        		// vertices will be created.
        		if ((keys.size() != data.size()) || (keys.size() != edges.size()))
        		{
        			cerr << "ERROR: Insufficient input." << endl;
        			num_of_vertices = 0;
        			return;
        		}
        		
        		// allocate space for vertex pointers
		    	num_of_vertices = keys.size();
		    	vertices = new Vertex<D,K>*[num_of_vertices];

		    	// this for loop initializes all vertices
		    	for (int i = 0; i < num_of_vertices; i++)
		    	{
		        	Vertex<D, K>* new_vertex = new Vertex<D, K>(keys[i], data[i], edges[i].size()); //create a new vertex, adjacency list will be created later
		        
		        	vertices[i] = new_vertex; //add the vertex to the graph's list of the vertices 
		    	}
		    
		    	// this for loop initializes all vertex adjacency lists
		    	for (int j = 0; j < num_of_vertices; j++)
		    	{		    	
		    		int num_edges_at_vertex = edges[j].size();	// number of edges (adjacent vertices)
		    		
		    		for (int k = 0; k < num_edges_at_vertex; k++)
		    		{
		    			Vertex<D, K>* adj_vertex = this->get(edges[j][k]);	// get a pointer to the adjacent vertex
		    			
		    			vertices[j]->adj_list[k] = adj_vertex;	// add it to adjacency list
		    		}
		    	}
        	};
        
		~Graph()	// destructor
		{
			for (int i = 0; i < num_of_vertices; i++)	// deletes every vertex's adjacency list and the vertex itself
			{
				delete vertices[i]->adj_list;
				delete vertices[i];
			}	

		    	delete vertices;	// then, deletes the vertices array
		};
        
        	/*
        	get function.
        	
        	Purpose:
        	Find the vertex with a given key in a graph.
        	Returns a pointer to the vertex. Returns NULL
        	if key does not exist.
        	
        	Parameters:
        	- k: a key.
        	
        	Pre-conditions:
        	- A graph.
        	
        	Post-conditions:
        	- A graph.
        	*/
		Vertex<D, K>* get(K k)	// returns pointer to vertex with matching key
		{
			for (int i = 0; i < num_of_vertices; i++)	// go through all vertices
			{
				if (vertices[i]->key == k)	// if keys match, return pointer to vertex
					return vertices[i];
			}
			
			return NULL;	// if no match, return NULL
		};
		
		/*
		to_string function.
		
		Purpose:
		Print the keys, data, and adjacency lists of all
		vertices in a graph.
		*/
		string to_string() const
		{
			stringstream ss;
			
			if (num_of_vertices <= 0)
				return ss.str();
				
			for (int i = 0; i < num_of_vertices; i++)
			{
				ss << "Vertex " << vertices[i]->key << " (Data = " << vertices[i]->data << "): {";
				
				if (vertices[i]->num_of_edges > 0)
				{
					for (int j = 0; j < ((vertices[i]->num_of_edges) - 1); j++)
						ss << vertices[i]->adj_list[j]->key << ", ";
						
					ss << vertices[i]->adj_list[((vertices[i]->num_of_edges) - 1)]->key << "}";
					
					if (i != (num_of_vertices - 1))
						ss << endl;
				}
				else
				{
					ss << "}";
					
					if (i != (num_of_vertices - 1))
						ss << endl;
				}
			}
			
			return ss.str();
		};
};

/*
<< operator.

Purpose:
Print graphs.
*/
template<typename D, typename K>
ostream& operator<<(ostream& os, Graph<D, K> & g)
{
	os << g.to_string();
	return os;
};
