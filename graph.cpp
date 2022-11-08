// graph.cpp

#include <iostream>
#include <sstream>
#include <vector>
#include "vertex.cpp"
#include <bits/stdc++.h>
#include <queue>

using namespace std;

// Graph template class
template <typename D, typename K>
class Graph
{
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
		    	
		    	source = K();
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
		Vertex<D, K>* get(K k)	const // returns pointer to vertex with matching key
		{
			for (int i = 0; i < num_of_vertices; i++)	// go through all vertices
			{
				if (vertices[i]->key == k)	// if keys match, return pointer to vertex
					return vertices[i];
			}

			return NULL;	// if no match, return NULL
		};


		void bfs(K s)
		{
			//initializing every vertex in the graph to their default values
			for(int i = 0; i < num_of_vertices; i++)
			{ 
					vertices[i]->color = 0;
					vertices[i]->predecessor = NULL;
					vertices[i]->distance =INT_MAX; //change to infinity later on

			}
			Vertex <D,K> * source = this->get(s);
			
			if(source == NULL)	// incase the requested key is not in the graph
			{
				return;
			}
			
			// initialize source attributes
			source->color = 1;
			source->predecessor = NULL;
			source->distance = 0;
			
			this->source = source->key;

			queue <Vertex <D,K> *> q; //making a queue to store our Vertex pointers
			q.push(source);
			
			//while the queue is not empty there are still vertices that need to be checked
			while(q.empty() != true)
			{
				Vertex <D,K> * current;
				current = q.front(); //sets a placeholder vertex = to what is at the front of the queue for future reference
				q.pop();
				
				//will discover every undiscovered node from current's adjacency list and add them to the queue
				for(int p = 0; p < current->num_of_edges; p++)
				{ 


					Vertex <D,K>* newVertex = current->adj_list[p];
					
					if(newVertex->color == 0)
					{
						q.push(newVertex);
						newVertex->predecessor = current;
						newVertex->distance = newVertex->predecessor->distance +1;
					}
				}
				
				current->color = 1;
			}
		}
		
		/*void bfs_tree(K s)
		{
			K original_source = this->source;
			
			this->bfs(s);
			Vertex<D, K>* source = this->get(s);
			
			cout << source->key << endl;
			
			for (int i = 0; i < num_of_vertices; i++)
			{
				if()
			
			}
			
			cout << endl;
		
		
			this->bfs(original_source);
		}*/
		
			/*
			Vertex<D, K>* source = this->get(u);
			Vertex<D, K>* find = this->get(v);
			
			if (source == NULL || find == NULL)
			{
				cerr << "No path exists, one or more input keys are invalid." << endl;
				return;
			}
			
			if (source->key == find->key)
				cout << source->key;
			else if (find->predecessor == NULL)
				cout << "No path exists.";
			else
			{
				this->print_path(source->key, find->predecessor->key);
				cout << " -> " << find->key;
			}
			*/

		bool reachable(K u, K v)
		{
			K s = this->getSource();
			Graph <D,K> * copy = this;
			copy->bfs(u);
			Vertex <D,K> * endVert = copy->get(v);
			this->setSource(s);
			if(endVert == NULL)
			{ //if the vertex with key v is not in the bfs tree of u return false
				return false;
			}
			else
			{
				
				int finDist = endVert->distance;
				
				if(finDist == INT_MAX)
				{
					return false;
				}
				

				return true;
			}
			
		}
		
		void setSource(K k){
			source = k;
		
		
		}
		
		K getSource(){
			return source;
		}
		
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
			
			if (num_of_vertices <= 0)
				return ss.str();
				
			ss << "~~~~~~~~~~" << endl;
			
			ss << "ADJACENCY LISTS: " << endl;
			ss << this->print_adjacency_lists() << endl;
			
			ss << "~~~~~" << endl;
			
			if (source != K())
				ss << "VERTEX ATTRIBUTES (source is Vertex " << source << "): " << endl;
			else
				ss << "VERTEX ATTRIBUTES (no source): " << endl;
			
			ss << this->print_vertex_attributes() << endl;
			
			ss << "~~~~~~~~~~";
			
			return ss.str();
		};
		
	private:
		Vertex<D, K>* *vertices;	// array of vertex pointers
		int num_of_vertices;	// size of array
		K source;	// key of source vertex for bfs
		
		/*
		print_adjacency_lists function.
		
		Purpose:
		Print the adjacency lists of all
		vertices in a graph.
		*/
		string print_adjacency_lists() const
		{
			stringstream ss;
				
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
		
		
		
		
		
		/*
		print_vertex_attributes function.
		
		Purpose:
		Print the attributes of each vertex 
		in a graph.
		*/
		string print_vertex_attributes() const
		{
			stringstream ss;
				
			for (int i = 0; i < num_of_vertices; i++)
			{
				ss << "Vertex " << vertices[i]->key << " (Data = " << vertices[i]->data << "): {";
				
				// color
				if (vertices[i]->color)
					ss << "color = Black, ";
				else
					ss << "color = White, ";
					
				// predecessor
				if (vertices[i]->predecessor == NULL)
					ss << "π = None, ";
				else
					ss << "π = " << vertices[i]->predecessor->key << ", ";
					
				// distance
				if(vertices[i]->distance == INT_MAX)
					ss << "distance = ∞";
				else
					ss << "distance = " << vertices[i]->distance;
					
				// end of a vertex
				if (i != (num_of_vertices - 1))
					ss << "}" << endl;
				else
					ss << "}";
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
