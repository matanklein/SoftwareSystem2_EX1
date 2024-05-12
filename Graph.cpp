/*
    ID: 8240
    Mail: matank214@gmail.com
*/

#include "Graph.hpp"

ariel::Graph::Graph()
{
    this->size = 0;
}

void ariel::Graph::loadGraph(vector<vector<int>> graph, bool isDirected)
{
    int numRows = graph.size();
    for (size_t i = 0; i < numRows; i++)
    {
        if (graph[i].size() != numRows)
        {
            throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
    }
    if(!isDirected){
        for (size_t i = 0; i < numRows; i++)
        {
            for (size_t j = 0; j < numRows; j++)
            {
                if (graph[i][j] != graph[j][i])
                {
                    throw invalid_argument("Invalid graph: The graph is not undirected.");
                }
            }
        }
    }
    bool flag = true;
    bool isweight = false;
    for (size_t i = 0; i < numRows && flag; i++)
    {
        for (size_t j = 0; j < numRows && flag; j++)
        {
            if(graph[i][j] < 0){
                flag = false;
                ariel::Graph::weihgt = negative_weight;
            }
            if(graph[i][j] > 0){
                isweight = true;
            }
        }
    }
    if(flag && isweight){
        ariel::Graph::weihgt = Nonnegative_weights;
    }
    if(flag && !isweight){
        ariel::Graph::weihgt = no_weights;
    }
    this->graph = graph;
    this->size = graph.size();
    this->isDirected = isDirected;
}

int ariel::Graph::getEdges()
{
    if(this->size == 0)
    {
        return 0;
    }

    int edges = 0;
    for (size_t i = 0; i < this->size; i++)
    {
        for (size_t j = 0; j < this->size; j++)
        {
            if (this->graph[i][j] != 0)
            {
                edges++;
            }
        }
    }
    if (this->isDirected)
    {
        return edges;
    }
    return edges/2;
}

void ariel::Graph::printGraph()
{
    if(size == 0)
    {
        cout << "Graph is empty." << endl;
        return;
    }
    cout << "Graph with " << this->size << " vertices and " << this->getEdges() << " edges." << endl;
}
