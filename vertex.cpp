

template <typename D, typename K>
class Vertex{

    public:
        Vertex * adjList;
        
        Vertex(K k, D d){
            key = k;
            data = d;
           
        }

        void setEdges(vector <K> edges){
            adjList = new Vertex[edges.length()]
            
        }
        


        void setColor(int col){
            color = col;
        }
        D getdata(){ //getter for the vertex's data
            return data;

        }
        K getkey(){ //getter for the vertex's key
            return key;
        }

        





    private:

        int color;// 0 white, 1 grey, 2 black
        Vertex <D,K> predecessor; //check back later
        K key;
        D data;
        Vector <K> edges;
        



};
