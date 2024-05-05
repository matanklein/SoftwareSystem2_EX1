#include "Graph.hpp"

ariel::Graph::Graph()
{
    this->size = 0;
}

void ariel::Graph::loadGraph(vector<vector<int>> graph, bool isDirected = false)
{
    int numRows = graph.size();
    for (int i = 0; i < numRows; i++)
    {
        if (graph[i].size() != numRows)
        {
            cout << "Invalid graph: The graph is not a square matrix." << endl;
            return;
        }
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
    for (int i = 0; i < this->size; i++)
    {
        for (int j = 0; j < this->size; j++)
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
