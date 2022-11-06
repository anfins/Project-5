// test_graph.cpp

#include <iostream>
#include <vector>
#include "graph.cpp"

using namespace std;

Graph<string, string>* generate_graph(string fname)
{
	string line;
	ifstream infile(fname);
	
	vector<string> keys = {};
	vector<string> data = {};
	vector<vector<string>> adjs = {};
	
	if (infile.is_open())
	{
		while(getline(infile, line))
		{
	    		unsigned long delim = line.find(":");
	    		string key = line.substr(0, delim);
	    		string adj = line.substr(delim+1);
	    
	    		keys.push_back(key);
	    		data.push_back(key + " data");
	    		delim = adj.find(",");
	    		vector<string> adj_lst = {};
	    		
	    		while(delim != string::npos)
	    		{
				adj_lst.push_back(adj.substr(0, delim));
				adj = adj.substr(delim+1);
				delim = adj.find(",");
	    		}
	    		
	    		
	    		adj_lst.push_back(adj);
	    		adjs.push_back(adj_lst);
		}
	}
	
	Graph<string,string>* G = new Graph<string, string>(keys, data, adjs);
	
	return G;
}

int main() 
{
	vector<int> data{0, 1, 2, 3, 4, 5};
	vector<char> keys{'A', 'B', 'C', 'D', 'E', 'F'};
	
	vector<char> adj1{'B', 'C'};
	vector<char> adj2{'A', 'D'};
	vector<char> adj3{'A', 'D'};
	vector<char> adj4{'B', 'C', 'E'};
	vector<char> adj5{'D'};
	vector<char> adj6;
	vector< vector<char> > edges = {adj1, adj2, adj3, adj4, adj5, adj6};
	
	Graph<int, char> graph1 = Graph<int, char>(keys, data, edges);
	
	cout << "GRAPH 1 ADJACENCY LISTS:" << endl;
	cout << graph1 << endl << endl;
	
	// using "graph_description.txt"
	Graph<string,string>* graph2 = generate_graph("graph_description.txt");
	
	cout << "EXAMPLE GRAPH ADJACENCY LISTS:" << endl;
	cout << *graph2 << endl;
	
	delete graph2;

    	return 0;
}
