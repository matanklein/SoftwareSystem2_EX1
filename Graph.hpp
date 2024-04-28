#include <iostream>
#include <vector>
using namespace std;
namespace ariel{

class Graph{

    private:
        vector<vector<int>> graph;
        int size;
        bool isDirected;

    public:
        Graph();
        ~Graph();
        void loadGraph(vector<vector<int>>, bool = false);
        void printGraph();
        int getSize(){
            return size;
        }
        int getEdge(int i, int j){
            return graph[i][j];
        }
        int getEdges();
    
};

}