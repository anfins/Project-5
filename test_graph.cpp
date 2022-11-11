/* test_graph.cpp

Programmers: Jorden Anfinson, Eduardo Jara, Jamaal Wairegi
Course: CS 271 01: Data Structures
Professor: Prof. Stacey Truex
Date: 11.11.2022
*/

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
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
	vector<int> data1{0, 1, 2, 3, 4, 5};
	vector<char> keys1{'A', 'B', 'C', 'D', 'E', 'F'};

	vector<char> adj1_1{'B', 'D'};
	vector<char> adj2_1{'A', 'C'};
	vector<char> adj3_1{'B', 'D'};
	vector<char> adj4_1{'A', 'C', 'E'};
	vector<char> adj5_1{'D', 'F'};
	vector<char> adj6_1;
	vector< vector<char> > edges1 = {adj1_1, adj2_1, adj3_1, adj4_1, adj5_1, adj6_1};

	Graph<int, char> graph1 = Graph<int, char>(keys1, data1, edges1);
	
	assert(graph1.get('B')->get_data() == 1);
	assert(graph1.get('F')->get_data() == 5);
	assert(graph1.get('A')->get_key() == 'A');
	assert(graph1.get('c') == NULL);
	assert(graph1.get('C') != NULL);
	assert((graph1.get('C')->get_data() * 2 )== graph1.get('E')->get_data());
	
	vector<string> keys2{};
	vector<int> data2{};
	
	vector< vector<string> > edges2{};
	
	Graph<int, string> graph2 = Graph<int, string>(keys2, data2, edges2);
	
	assert(graph2.get("hello") == NULL);
	assert(graph2.get("") == NULL);
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
    	
    	// our tests
    	vector<float> data1{3.141, 0.375, 0.500, 3.333, 0.001};
	vector<int> keys1{40, 30, 20, 10, 0};

	vector<int> adj1_1{30, 20};
	vector<int> adj2_1{10};
	vector<int> adj3_1{10};
	vector<int> adj4_1{40};
	vector<int> adj5_1{10};
	vector< vector<int> > edges1 = {adj1_1, adj2_1, adj3_1, adj4_1, adj5_1};

	Graph<float, int> graph1 = Graph<float, int>(keys1, data1, edges1);
	
	assert(graph1.reachable(40, 10));
	assert(graph1.reachable(20, 20));
	assert(graph1.reachable(30, 10));
	assert(graph1.reachable(30, 40));
	assert(!graph1.reachable(40, 0) == graph1.reachable(0, 40));
	
	
    	vector<string> data2{"house", "ice", "jungle", "keep", "laundry", "mop"};
	vector<char> keys2{'h', 'i', 'j', 'k', 'l', 'm'};

	vector<char> adj1_2{'j'};
	vector<char> adj2_2{'h', 'k'};
	vector<char> adj3_2{'k'};
	vector<char> adj4_2{'h'};
	vector<char> adj5_2{'k'};
	vector<char> adj6_2{};
	vector< vector<char> > edges2 = {adj1_2, adj2_2, adj3_2, adj4_2, adj5_2, adj6_2};

	Graph<string, char> graph2 = Graph<string, char>(keys2, data2, edges2);
	
	int num_vertices = keys2.size();
	
	// check that Vertex m is completely isolated
	for (int i = 0; i < num_vertices - 1; i++)
		assert(!graph2.reachable(graph2.get(keys2[i])->get_key(), 'm'));
		
	assert(graph2.reachable('l', 'j'));
	assert(!graph2.reachable('j', 'i'));
	assert(graph2.reachable('h', 'k'));
	assert(!graph2.reachable('h', 'i'));
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
    	
    	vector<bool> data1{false, false, false, true, true};
	vector<long long> keys1{10000, 20000, 30000, 40000, 50000};

	vector<long long> adj1_1{20000, 30000};
	vector<long long> adj2_1{40000, 50000};
	vector<long long> adj3_1{40000};
	vector<long long> adj4_1{};
	vector<long long> adj5_1{40000};
	vector< vector<long long> > edges1 = {adj1_1, adj2_1, adj3_1, adj4_1, adj5_1};

	Graph<bool, long long> graph1 = Graph<bool, long long>(keys1, data1, edges1);
	
	graph1.bfs(10000);
	
	// Vertex 10000 is the source
	assert(((graph1.get(10000)->get_predecessor() == 0) == (graph1.get(10000)->get_color() == true)) == (graph1.get(10000)->get_distance() == 0));
	
	int num_vertices = keys1.size();
	
	// all vertices in graph 1 should be discoverable from 10000
	for (int i = 0; i < num_vertices - 1; i++)
		assert((graph1.get(keys1[i])->get_color() == true));
		
	assert(graph1.get(20000)->get_predecessor() == 10000);
	assert(graph1.get(30000)->get_predecessor() == 10000);
	assert(graph1.get(40000)->get_predecessor() == 20000);
	assert(graph1.get(50000)->get_predecessor() == 20000);
	assert(graph1.get(30000)->get_distance() == 1);
	
	graph1.bfs(40000);
	
	for (int i = 0; i < num_vertices; i++)
	{
		if (graph1.get(keys1[i])->get_key() != 40000)
			assert((graph1.get(keys1[i])->get_color() == false));
	}
	
	// Vertex 40000 is the source
	assert(((graph1.get(40000)->get_predecessor() == 0) == (graph1.get(40000)->get_color() == true)) == (graph1.get(40000)->get_distance() == 0));
	
	graph1.bfs(50000);
	
	// only Vertex 40000 is reachable from 50000
	assert(graph1.get(40000)->get_color() == true);
	assert(graph1.get(40000)->get_distance() == 1);
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
    	
   	vector<short int> data1{2, 3, -5, 80};
	vector<u_char> keys1{'!', '?', ';', '.'};

	vector<u_char> adj1_1{'!', '?'};
	vector<u_char> adj2_1{'.', ';'};
	vector<u_char> adj3_1{'!'};
	vector<u_char> adj4_1{};
	vector< vector<u_char> > edges1 = {adj1_1, adj2_1, adj3_1, adj4_1};
	
	Graph<short int, u_char> graph1 = Graph<short int, u_char>(keys1, data1, edges1);

	stringstream buffer1;
	streambuf* prevbuf1 = cout.rdbuf(buffer1.rdbuf());
	graph1.print_path('!', '!');
	cout.rdbuf(prevbuf1);
	
	assert(buffer1.str() == "!");
	
	stringstream buffer2;
	streambuf* prevbuf2 = cout.rdbuf(buffer2.rdbuf());
	graph1.print_path('?', '!');
	cout.rdbuf(prevbuf2);
	
	assert(buffer2.str() == "? -> ; -> !");
	
   	vector<double> data2{1.111, 2.222, 3.333, 4.444, 5.555, 6.666};
	vector<double> keys2{10.2, 30.4, 50.6, 70.8, 90.1, 100.0};

	vector<double> adj1_2{30.4};
	vector<double> adj2_2{90.1};
	vector<double> adj3_2{10.2, 70.8};
	vector<double> adj4_2{100.0};
	vector<double> adj5_2{};
	vector<double> adj6_2{90.1};
	vector< vector<double> > edges2 = {adj1_2, adj2_2, adj3_2, adj4_2, adj5_2, adj6_2};
	
	Graph<double, double> graph2 = Graph<double, double>(keys2, data2, edges2);
	
	stringstream buffer3;
	streambuf* prevbuf3 = cout.rdbuf(buffer3.rdbuf());
	graph2.print_path(10.2, 90.1);
	cout.rdbuf(prevbuf3);
	
	assert(buffer3.str() == "10.2 -> 30.4 -> 90.1");
	
	stringstream buffer4;
	streambuf* prevbuf4 = cout.rdbuf(buffer4.rdbuf());
	graph2.print_path(50.6, 90.1);
	cout.rdbuf(prevbuf4);
	
	assert(buffer4.str() == "50.6 -> 10.2 -> 30.4 -> 90.1"); // you can make it to 90.1 to 50.6 by going to 70.8 OR 10.2, but since 10.2 appears in 50.6's adj list first, that path is prioritizes (it is *a* shortest path) 
	
	stringstream buffer5;
	streambuf* prevbuf5 = cout.rdbuf(buffer5.rdbuf());
	graph2.print_path(90.1, 30.4);
	cout.rdbuf(prevbuf5);
	
	assert(buffer5.str() == "No path exists.");
	
   	vector<int> data3{};
	vector<int> keys3{};
	vector< vector<int> > edges3{};
	
	Graph<int, int> graph3 = Graph<int, int>(keys3, data3, edges3);
	
	stringstream buffer6;
	streambuf* prevbuf6 = cout.rdbuf(buffer6.rdbuf());
	graph3.print_path(4, 10);
	cout.rdbuf(prevbuf6);
	
	assert(buffer6.str() == "No path exists.");
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
	
	// also testing out that dfs works correctly
	assert(graph1.get(3.1)->get_dis_time() == 1);
	assert(graph1.get(3.1)->get_predecessor() == 0.0);	// no predecessor, key returned is default key value
	assert(graph1.get(4.2)->get_dis_time() == 2);
	assert(graph1.get(6.4)->get_dis_time() == 3);
	assert(graph1.get(6.4)->get_predecessor() == graph1.get(4.2)->get_key());
	assert(graph1.get(5.3)->get_fin_time() == 7);
	
	
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
	
	
	vector<string> keys3{"cs271"};
	vector<float> data3{3.00};
	
	vector<string> adj1_3{"cs271"};
	vector< vector<string> > edges3{adj1_3};
	
	Graph<float, string> graph3 = Graph<float, string>(keys3, data3, edges3);
	
	assert(graph3.edge_class("cs271", "cs271") == "back edge");
	assert(graph3.get("cs271")->get_dis_time() == 1);
	assert(graph3.get("cs271")->get_fin_time() == 2);
	assert(graph3.get("cs271")->get_predecessor() == "");	// no predecessor, key returned is default key value
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
