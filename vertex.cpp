/* vertex.cpp

Programmers: Jorden Anfinson, Eduardo Jara, Jamaal Wairegi
Course: CS 271 01: Data Structures
Professor: Prof. Stacey Truex
Date: 11.11.22
*/

#include <iostream>
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

// Vertex template class
template <typename D, typename K>
class Vertex
{
	public:
		D data;
		K key;
	
		bool color;	// false (0) =  white, true (1) =  black (used for BFS)
		int distance;	// distance from source (used for BFS)
		Vertex* predecessor; // pointer to predecessor vertex (used for BFS)
		
		int dis_time;	// time of discovery (used for DFS/edge_class)
		int fin_time; // time of finished being discovered (used for DFS/edge_class)
	
		Vertex* *adj_list;	// array of pointers to adjacent vertexes
		int num_of_edges;	// size of array

        	Vertex(K k, D d, int adj_list_size = 0)	// constructor for given data, key, and adjacency list size
        	{
            		data = d;
            		key = k;
            		color = false;
            		distance = INT_MAX;
            		predecessor = NULL;
            		dis_time = 0;
            		fin_time = 0;
            
		    	if (adj_list_size < 0)	// check if adjacency list is the right size
		    		num_of_edges = 0;
		    	else
		    		num_of_edges = adj_list_size;
		    		
		    	adj_list = new Vertex*[num_of_edges];
        	}
        	
        	// the following functions are used to test the attributes of vertices in a graph
        	
        	// get_key
        	// Returns the key of a vertex
        	K get_key() const
        	{
        		return key;
        	};
        	
        	// get_data
        	// Returns the data of a vertex
        	D get_data() const
        	{
        		return data;
        	};
		
        	// get_color
        	// Returns the color a vertex in latest bfs/dfs
		bool get_color() const
        	{
        		return color;
        	};
        	
        	// get_distance
        	// Returns the distance a vertex is from the source in latest bfs
        	int get_distance() const
        	{
        		return distance;
        	};
        	
        	// get_predecessor
        	// Returns the key of the predecessor of a vertex in latest bfs/dfs
        	K get_predecessor() const
        	{
        		if (predecessor == NULL)
        			return K();
        		
        		return predecessor->key;
        	};
        	
        	// get_dis_time
        	// Returns the time vertex was discovred in latest dfs
        	int get_dis_time()
        	{
        		return dis_time;
        	};
        	
        	// get_fin_time
        	// Returns the time vertex finished being discovery in latest dfs
        	int get_fin_time()
        	{
        		return fin_time;
        	};
        	
        	// get_edges
        	// Returns string of all keys of edges vertex has, separated by spaces
        	string get_edges()
        	{
    			stringstream ss;
    			
        		for (int i = 0; i < num_of_edges - 1; i++)
        			ss << adj_list[i]->key << " ";
        			
        		ss << adj_list[num_of_edges - 1]->key;
        		
        		return ss.str();
        	};
};
