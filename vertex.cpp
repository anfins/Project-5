

template <typename D, typename K>
class Vertex{

    public:
        
        Vertex(K k, D d, vector <K> e){
            key = k;
            data = d;
            edges = e;
        }

        





    private:
        int color;// 0 white, 1 grey, 2 black
        Vertex <D,K> predecessor; //check back later
        K key;
        D data;
        Vector <K> edges;
        



};