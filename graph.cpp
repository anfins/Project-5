
/* graph.cpp
Programmers: Jorden Anfinson, Eduardo Jara, Jamaal Wairegi
Course: CS 271 01: Data Structures
Professor: Prof. Stacey Truex
Date: 11.11.2022
*/

#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include "vertex.cpp"

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
        			vertices = new Vertex<D,K>*[num_of_vertices];
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
		    	max_distance = 0;
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

        	/*
        	bfs (Breadth-First Search) function.
        	
        	Purpose:
        	Search for every discoverable
        	vertex from a given source vertex.

        	Parameters:
        	- s: a source vertex key.
        	- print: flag variable for printing the 
        	tree associated with bfs'd graph (for bfs_tree
        	function).
        	
        	Pre-conditions:
        	- A graph.
        	
        	Post-conditions:
        	- A trees of the graph's vertexes, with
        	Vertex s as its root.
        	*/
		void bfs(K s, bool print = false)
		{
			if (num_of_vertices <= 0)
			{
				if (print)
					cout << "";
				
				return;
			}

			//initializing every vertex in the graph to their default values
			for(int i = 0; i < num_of_vertices; i++)
			{
					vertices[i]->color = 0;
					vertices[i]->predecessor = NULL;
					vertices[i]->distance =INT_MAX;

					vertices[i]->dis_time = 0;
					vertices[i]->fin_time = 0;
			}

			Vertex <D,K> * source = this->get(s);

			if(source == NULL)	// incase the requested key is not in the graph
			{
				if (print)
					cout << "";
				
				return;
			}

			// initialize source attributes
			source->color = 1;
			source->predecessor = NULL;
			source->distance = 0;
			
			max_distance = 0;
			
			// print at level 0
			if (print)
				cout << source->key << endl;

			this->source = source->key;

			queue <Vertex <D,K> *> q; //making a queue to store our Vertex pointers
			q.push(source);

			//while the queue is not empty there are still vertices that need to be checked
			while(q.empty() != true)
			{
				Vertex <D,K>* current;
				current = q.front(); // sets a placeholder vertex = to what is at the front of the queue for future reference
				q.pop();
				
				//will discover every undiscovered node from current's adjacency list and add them to the queue
				for(int p = 0; p < current->num_of_edges; p++)
				{
					Vertex <D,K>* newVertex = current->adj_list[p];

					if (newVertex->color == 0)
					{	
						newVertex->predecessor = current;
						
						newVertex->distance = newVertex->predecessor->distance + 1;
						max_distance = newVertex->distance;
						
						newVertex->color = 1;
						
						q.push(newVertex);
						
						// print at current level (only print the space if still at distance x and its not the final vertex at distance x)
						if (print)
							cout << newVertex->key << " ";
					}
				}

				current->color = 1;
				
				// end of level (only print once all vertices at distance x have been printed)
				if (print && !q.empty())
					cout << endl;
			}
		};

        	/*
        	bfs_tree function.
        	
        	Purpose:
        	Prints the contents of a bredth-first searched
        	graph as a tree. Simply passes in 'true' for
        	'print' in bfs function.

        	Parameters:
        	- s: a source vertex key.
        	
        	Pre-conditions:
        	- A graph.
        	
        	Post-conditions:
        	- A graph that has been breadth-first searched
        	from source s.
        	*/
        	void bfs_tree(K s)
        	{
        		this->bfs(s, true);
        	}
	    
    void bfs_tree(K k ){
      this->bfs(k); 
      for(int i = 0; i <=maxdistance; i++){
        for(int k =0; k < num_of_vertices; k++){
          if(vertices[k]->distance == i){

            cout << vertices[k]->key << " ";

          }

        }
        cout << endl;
      }
    }

        	/*
        	reachable function.
        	
        	Purpose:
        	Determines whether a vertex can be
        	discovered from another vertex.
        	
        	Parameters:
        	- u: a source vertex key.
        	- v: a key for the vertex to find.
        	
        	Pre-conditions:
        	- A graph.
        	
        	Post-conditions:
        	- A graph that has been breadth-first searched
        	from Vertex u.
        	*/
		bool reachable(K u, K v)
		{
			this->bfs(u); //calls bfs to initialize the vertices in the graph from the source vertex u
      			//this will initialize all of the vertices in our graph, if a vertex is not reachable from the source vertex, its distance will still be INT_MAX after this call

			Vertex<D, K>* source = this->get(u); //creating a pointer to the source vertex

			if (source == NULL)
				return false;

			Vertex<D, K>* find = this->get(v); //creating a pointer to the vertex we need to find

			//if the vertex with key v is not in the bfs tree of u, or if distance is infinity, return false
			if (find == NULL || find->distance == INT_MAX)
				return false;

			return true;
		};

        	/*
        	print_path function.
        	
        	Purpose:
        	Prints the path from one vertex
        	to another in a graph. Prints no
        	path if no such path exists.

        	Parameters:
        	- u: a start vertex key.
        	- v: an end vertex key.
        	
        	Pre-conditions:
        	- A graph.
        	
        	Post-conditions:
        	- A graph that has been breadth-first searched
        	from Vertex u.
        	*/
		void print_path(K u, K v)
		{
			if (num_of_vertices <= 0)
			{
				cout << "No path exists.";
				return;
			}

			this->bfs(u);	// breadth-first search from u

			this->print_path_recursive(u, v);	// recursive functiion for print_path
		};

        	/*
        	edge_class function.
        	
        	Purpose:
        	Identifies the type of edge two given vertices possess.
        	Returns a string of the type of ege.

        	Parameters:
        	- u: a vertex key for which an edge begins.
        	- v: another vertex key for which the edge ends.
        	
        	Pre-conditions:
        	- A graph.
        	
        	Post-conditions:
        	- A graph that has been depth-first searched.
        	*/
		string edge_class(K u, K v)
		{
			this->dfs();

			Vertex <D,K>* v1 = this->get(u);
			Vertex <D,K>* v2 = this->get(v);

			if (v1 == NULL || v2 == NULL)	// no edge (either u or v does not exist)
				return "no edge";

			bool edge_exists = false;

			for (int i = 0; i < v1->num_of_edges; i++)	// check if v2 is in v1's adjacency list (edge exists)
			{
				if (v1->adj_list[i] == v2)
				{
					edge_exists = true;
					break;
				}
			}

			if(edge_exists)
			{
				if (v2->predecessor == v1)	// tree edge (v is discovered via u)
					return "tree edge";
				else if ((v2->dis_time > v1->dis_time) && (v2->fin_time < v1->fin_time))	// forward edge (v is descendant of u) (v has completed )
					return "forward edge";
				else if (((v1->dis_time > v2->dis_time) && (v1->fin_time < v2->fin_time)) || (v1 == v2))	// back edge (u is descendant of v OR (u, v) is a self edge)
					return "back edge";
				else				// cross edge (any other type of edge--connects non-descendants)
					return "cross edge";
			}

			return "no edge";	// no edge (u and v exist, but (u, v) is not an edge)
		};

		/*
		to_string function.

		Purpose:
		Prints all vertices of
		a graph.
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

			ss << "~~~~~~~~~~" << endl;

			return ss.str();
		};

	private:
		Vertex<D, K>* *vertices;	// array of vertex pointers
		int num_of_vertices;	// size of array
		K source;	// key of source vertex (for latest bfs)
		int time;	// global time variable (for dfs)
		int max_distance;	//track max distance for bfs_tree function

        	/*
        	dfs (Depth-First Search) function.
        	
        	Purpose:
        	Search for every vertex, beginning at
        	the furthest depth.

        	Parameters:
        	- N/A.
        	
        	Pre-conditions:
        	- A graph.
        	
        	Post-conditions:
        	- A forest of trees of the graph's vertexes.
        	*/
		void dfs()
		{
			if (num_of_vertices <= 0)
				return;

			source = K();
			time = 0;	// global time variable

			// initialize every vertex's attributes
			for (int i = 0; i < num_of_vertices; i++)
			{
				vertices[i]->color = 0;
				vertices[i]->predecessor = NULL;

				vertices[i]->distance = INT_MAX;
			}

			// for every vertex of the graph, visit if white (undiscovered)
			for(int i = 0; i < num_of_vertices ; i++)
			{
				if(vertices[i]->color == false)
				{
					this->dfs_visit(vertices[i]->key);
				}
			}
		};

        	/*
        	dfs_visit function.
        	
        	Purpose:
        	Visit the vertices of a vertex's adjacency
        	list and mark the discovery and finish time.

        	Parameters:
        	-u: a vertex key.
        	
        	Pre-conditions:
        	- A graph.
        	
        	Post-conditions:
        	- A graph whose vertices from Vertex u to some other
        	vertex have been discovered.
        	*/
		void dfs_visit(K u)
		{
			time = time + 1;

			Vertex<D,K>* v = this->get(u);

			v->dis_time = time;	// mark discovery time
			v->color = true;

			// for every vertex in u's adjacency list, if that vertex is white, make u it's predecessor and visit it's adjacency lists recursively
			for(int p = 0; p < v->num_of_edges; p++)
			{
				if( v->adj_list[p]->color == false)
				{
					v->adj_list[p]->predecessor = v;
					this->dfs_visit(v->adj_list[p]->key);
				}
			}

			time = time + 1;
			v->fin_time = time;	// mark finish time
		};

        	/*
        	print_path_recursive function.
        	
        	Purpose:
        	Recursive function for print_path.
        	*/
		void print_path_recursive(K u, K v)
		{
			Vertex<D, K>* source = this->get(u);
			Vertex<D, K>* find = this->get(v);

			if (source == NULL || find == NULL)	// if find or source are null, path does not exist
				cout << "No path exists.";
			else if (find == source)		// if find = source, print source (path has been found)
				cout << source->key;
			else if (find->predecessor == NULL)	// if find's predecessor is null, no path exists
				cout << "No path exists.";
			else					// if find is an actual vertex and has a predecessor, then print its predecessor
			{
				this->print_path_recursive(source->key, find->predecessor->key);
				cout << " -> " << find->key;
			}
		};

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
				// beginning bracket
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
				if (source != K())
				{
					if (vertices[i]->distance == INT_MAX)
						ss << "distance = ∞, ";
					else
						ss << "distance = " << vertices[i]->distance << ", ";
				}
				else
				{
					ss << "distance = N/A, ";
				}

				// discovery and finish time
				if (source == K())
				{
					ss << "discovery = " << vertices[i]->dis_time << ", ";

					ss << "finish = " << vertices[i]->fin_time;
				}
				else
				{
					ss << "discovery = N/A, ";

					ss << "finish = N/A";
				}

				// end bracket
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
