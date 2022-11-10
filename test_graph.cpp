/* test_graph.cpp

Programmers: Jorden Anfinson, Eduardo Jara, Jamaal Wairegi
Course: CS 271 01: Data Structures
Professor: Prof. Stacey Truex
Date: 11.11.22
*/

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <queue>
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

void test_get(Graph<string,string>* G) 
{
	// example tests
    	try 
    	{
		if (G->get("S") == nullptr || G->get("S")->data != "S data") 
		{
		    	cout << "Incorrect result getting vertex \"s\"" << endl; 
		}
		
		if (G->get("a") != nullptr) 
		{
			cout << "Incorrect result getting non-existant vertex \"a\"" << endl;
		}
    	} 
    	catch (exception& e) 
    	{
        	cerr << "Error getting vertex from graph : " << e.what() << endl;
    	}
    	
    	// our tests
	vector<int> data{0, 1, 2, 3, 4, 5};
	vector<char> keys{'A', 'B', 'C', 'D', 'E', 'F'};

	vector<char> adj1{'B', 'D'};
	vector<char> adj2{'A', 'C'};
	vector<char> adj3{'B', 'D'};
	vector<char> adj4{'A', 'C', 'E'};
	vector<char> adj5{'D', 'F'};
	vector<char> adj6;
	vector< vector<char> > edges = {adj1, adj2, adj3, adj4, adj5, adj6};

	Graph<int, char> graph = Graph<int, char>(keys, data, edges);
	
	assert(graph.get('B')->get_data() == 1);
	assert(graph.get('F')->get_data() == 5);
	assert(graph.get('A')->get_key() == 'A');
	assert(graph.get('c') == NULL);
	assert(graph.get('C') != NULL);
	assert((graph.get('C')->get_data() * 2 )== graph.get('E')->get_data());
}

void test_reachable(Graph<string,string>* G) 
{
	// example tests
    	try 
    	{
		if (!G->reachable("R", "V")) 
		{
		    	cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
		}
		
		if (!G->reachable("X", "W")) 
		{
		    	cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
		}
		
		if (G->reachable("S", "A")) 
		{
		    	cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
		}
    	} 
    	catch (exception& e) 
    	{
        	cerr << "Error testing reachable : " << e.what() << endl;
    	}
}

void test_bfs(Graph<string,string>* G) 
{
	// example tests
	try 
    	{
        	G->bfs("T");
        	
        	string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        	int distances[8] = {3,2,1,1,0,2,1,2};
        	
        	for (int i = 0; i < 8; i++)
        	{
            		if (G->get(vertices[i])==nullptr || G->get(vertices[i])->distance!=distances[i]) 
            		{
                		cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"t\"" << endl;
            		}
        	}
    	} 
    	catch (exception& e) 
    	{
    		cerr << "Error testing bfs : " << e.what() << endl;
    	}
   	
}

void test_print_path(Graph<string,string>* G) 
{
	// example tests
    	try 
    	{
		stringstream buffer;
		
		streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
		
		G->print_path("T", "V");
		
		cout.rdbuf(prevbuf);
		
		if (buffer.str()!="T -> S -> R -> V") 
		{
		    	cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
		}
    	} 
    	catch (exception& e) 
    	{
        	cerr << "Error testing print path : " << e.what() << endl;
    	}
}

void test_edge_class(Graph<string,string>* G) 
{
	// examples tests
    	try 
    	{
		string e_class =  G->edge_class("R", "V"); // tree edge
		
		if (e_class != "tree edge") 
		{
		    cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
		}
		
		e_class = G->edge_class("X", "U"); // back edge
		
		if (e_class != "back edge") 
		{
		    cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
		}
		
		e_class =  G->edge_class("R", "U"); // no edge
		
		if (e_class != "no edge") 
		{
		    cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
		}
		
		e_class = G->edge_class("T", "W"); // forward edge
		
		if (e_class != "forward edge") 
		{
		    cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
		}
		
		e_class = G->edge_class("T", "S"); // cross edge
		
		if (e_class != "cross edge") 
		{
		    cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
		}
    	} 
    	catch (exception& e) 
    	{
        	cerr << "Error testing edge class : " << e.what() << endl;
    	}
    	
    	// our tests
	vector<unsigned long int> data1{10392001, 679200, 404040, 3678591};
	vector<float> keys1{3.1, 4.2, 5.3, 6.4};

	vector<float> adj1_1{3.1, 4.2, 5.3, 6.4};
	vector<float> adj2_1{6.4};
	vector<float> adj3_1{4.2, 6.4};
	vector<float> adj4_1{3.1};
	vector< vector<float> > edges1 = {adj1_1, adj2_1, adj3_1, adj4_1};

	Graph<unsigned long int, float> graph1 = Graph<unsigned long int, float>(keys1, data1, edges1);
	
	assert(graph1.edge_class(5.3, 4.2) == "cross edge");
	assert(graph1.edge_class(3.1, 5.3) == "tree edge");
	assert(graph1.edge_class(6.4, 3.1) == "back edge");
	assert(graph1.edge_class(3.1, 6.4) == "forward edge");
	assert(graph1.edge_class(3.1, 3.1) == "back edge");	// self edge should still be back edge
	
	vector<bool> data2{true, false, true, true, false};
	vector<string> keys2{"We will get an A", "We will get an F", "We will get bonus points", "We will get free pizza", "The next exam will be easy"};

	vector<string> adj1_2{"We will get bonus points", "We will get free pizza"};
	vector<string> adj2_2{"We will get an A", "We will get free pizza"};
	vector<string> adj3_2{"We will get bonus points", "The next exam will be easy"};
	vector<string> adj4_2{"The next exam will be easy"};
	vector<string> adj5_2{"We will get an A"};
	vector< vector<string> > edges2 = {adj1_2, adj2_2, adj3_2, adj4_2, adj5_2};

	Graph<bool, string> graph2 = Graph<bool, string>(keys2, data2, edges2);
	
	assert(graph2.edge_class("We will get an F", "We will get an A") == "cross edge");
	assert(graph2.edge_class("We will get an A", "The next exam will be easy") == "no edge");
	assert(graph2.edge_class("The next exam will be easy", "We will get an A") == "back edge");
	assert(graph2.edge_class("We will get an A", "We will get free pizza") == "tree edge");
	assert(graph2.edge_class("We will get free pizza", "The next exam will be easy") == "cross edge");	// would be a tree edge, but due to the ordering of the adj list, the vertex "The next exam will be easy"'s predecessor is the vertex "We will get bonus points", even though "We will get free pizza" also leads to "The next exam will be easy".
	assert(graph2.edge_class("We will get bonus points", "The next exam will be easy") == "tree edge");
	assert(graph2.edge_class("hello", "world") == "no edge");
}

/*
void test_bfs_tree(Graph<string,string>* G) 
{
    	try 
    	{
        	stringstream buffer;
        	streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        	
        	G->bfs_tree("T");
        	cout.rdbuf(prevbuf);
        	
        	if (buffer.str() != "T\nS U W\nR Y X\nV") 
        	{
            		cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n" << buffer.str() << endl;
        	}
    	} 
    	catch (exception& e) 
    	{
        	cerr << "Error testing bfs tree : " << e.what() << endl;
    	}
}
*/

int main()
{
	string file = "graph_description.txt";
	Graph<string,string>* graph = generate_graph(file);

	test_get(graph);
	test_reachable(graph);
  	test_bfs(graph);
	test_print_path(graph);
	test_edge_class(graph);
	//test_bfs_tree(graph);
	
	delete graph;
	
	cout << "All tests passed successfully" << endl;

    	return 0;
}
