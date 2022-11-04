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
        Vertex * vertices;


        Graph(vector <K> k, vector <D> d, vector<vector<K>> e){

            //double check for disconnected nodes in final test case
            vertices = new Vertex*[k.length()];
            keys = k;
            data = d;
            edges = e;

            //does the graph need a head??
            for(int i = 0; i < keys.length(); i++){
                Vertex * newVert = new Vertex(keys[i], data[i]); //create a new vertex consisting of the attributes from the lists from the parameters
                *newVert.setColor(0); //initialize the color of the vertex to white
                vertices[i] == newVert; //add the vertex to the graph's list of the vertices 


            }
            for(int j = 0; j < vertices.length(); j++){
                vertices[j]
            }
        }


        ~Graph(){
            //in this we need to unallocate the memory that has been allocated for each vertex

            
        }

/*
        Vertex * get(K k){

            //returns the pointer to some vertex in the array given a key

            for(int i = 0; i < vertices.length(); i++){ //goes through all the vertices in an array
                if(i.getkey() == k){
                    return i;
                }
            

            }

            return D(); //return the default type if a vertex with the given key is not found
        }


*/
    private:
        vector <K> keys;
        vector <D> data;
        vector<vector<K>> edges;


    

};
