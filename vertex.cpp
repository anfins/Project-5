// vertex.cpp

#include <iostream>
#include <bits/stdc++.h>
#include <set>

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

        	Vertex(K k, D d, int adj_list_size = 0)	// constructor for given data, key, and adjacency list (size)
        	{
            		data = d;
            		key = k;
            		color = false;
            		distance = INT_MAX;
            		predecessor = NULL;
            		dis_time = 0;
            		fin_time = 0;
            
		    	if (adj_list_size <= 0)	// check if adjacency list is the right size
		    	{
		    		adj_list = NULL;
		    		num_of_edges = 0;
		    	}
		    	else
		    	{
		    		adj_list = new Vertex*[adj_list_size];
				num_of_edges = adj_list_size;
			}
        	}
        	
        	K get_key() const
        	{
        		return key;
        	};
        	
        	D get_data() const
        	{
        		return data;
        	};
		
		bool get_color() const
        	{
        		return color;
        	};
        	
        	int get_distance() const
        	{
        		return distance;
        	};
        	
        	K get_predecessor() const
        	{
        		return predecessor->key;
        	};
        	
        	int get_dis_time()
        	{
        		return dis_time;
        	};
        	
        	int get_fin_time()
        	{
        		return fin_time;
        	};
        	
        	set<K>* get_edges()	const
        	{
        		set<K> e;
        		
        		for (int i = 0; i < num_of_edges; i++)
        			e.insert(adj_list[i]->key);
        		
			set<K>* edges = &e;
			
        		return edges;
        	};
};
