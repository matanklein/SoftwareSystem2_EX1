/*
    ID: 8240
    Mail: matank214@gmail.com
*/

#include <vector>
#include <iostream>

#ifndef GRAPH_H
#define GRAPH_H

#define no_weights 0
#define Nonnegative_weights 1
#define negative_weight 2

using namespace std;
namespace ariel{

class Graph{

    private:
        vector<vector<int>> graph;
        size_t size;
        bool isDirected;
        int weihgt;

    public:
        Graph();
        ~Graph(){}
        void loadGraph(vector<vector<int>>, bool isdirec= true);
        void printGraph();
        size_t getSize() const{
            return size;
        }
        int getEdge(size_t i, size_t j) const{
            return graph[i][j];
        }
        bool getIsDirected() const{
            return isDirected;
        }
        int getEdges();
        int getWeight() const{
            return weihgt;
        }
    
};

}

#endif