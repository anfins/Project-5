#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#include <typeinfo>

template <typename D, typename K>
class Graph{

    public:


        Graph(vector <K> k, vector <D> d, vector<vector<K>> e){
            keys = k;
            data = d;
            edges = e;
        }



    private:
        vector <K> keys;
        vector <D> data;
        vector<vector<K>> edges;


        



};
