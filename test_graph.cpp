// test_graph.cpp

#include <iostream>
#include <vector>
#include "graph.cpp"

#include <queue>
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
void test_bfs(Graph<string,string>* G) {
    try {
        G->bfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int distances[8] = {3,2,1,1,0,2,1,2};
        for(int i = 0; i < 8; i++){
            if(G->get(vertices[i])==nullptr || G->get(vertices[i])->distance!=distances[i]) {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"t\"" << endl;
            }
        }
    } catch(exception& e) {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}
void test_reachable(Graph<string,string>* G) {
    try {
        if(!G->reachable("R", "V")) {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if(!G->reachable("X", "W")) {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if(G->reachable("S", "A")) {
            cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
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

  test_bfs(graph2);
	test_reachable(graph2);
	delete graph2;

    	return 0;
}
