#include "Algorithms.hpp"
#include <queue>
#include <iostream>

void ariel::Algorithms::shortestPath(Graph graph, int start, int end, int algo)
{
    vector<int> parent(graph.getSize());
    vector<int> distance(graph.getSize());
    if(algo == no_weights)
    {
        bfs(graph, start, parent, distance);
    }
    else if(algo == Nonnegative_weights)
    {
        dijkstra(graph, start, parent, distance);
    }
    else if(algo == negative_weight)
    {
        if(bellmanFord(graph, start, parent, distance) == failue)
        {
            cout << "Negative cycle detected" << endl;
        }
    }
    if(distance[end] == INF)
    {
        cout << "There is no path between " << start << " and " << end << endl;
    }
    string path = "";
    int u = end;
    while(u != null)
    {
        path = to_string(u) + " -> " + path;
        u = parent[u];
    }
    cout << path << endl;
}

int ariel::Algorithms::isConnected(Graph graph)
{
    if(graph.getSize() == 0)
    {
        return 1;
    }
    vector<int> parent(graph.getSize());
    vector<int> distance(graph.getSize());
    if(graph.getIsDirected())
    {
        for(int i = 0; i < graph.getSize(); i++)
        {
            bfs(graph, i, parent, distance);
            for(int j = 0; j < graph.getSize(); j++)
            {
                if(distance[j] == INF)
                {
                    return 0;
                }
            }
        }
    }
    else // undirected graph
    {
        bfs(graph, 0, parent, distance);
        for(int i = 0; i < graph.getSize(); i++)
        {
            if(distance[i] == INF)
            {
                return 0;
            }
        }
    }
    return 1;
}

void ariel::Algorithms::negativeCycle(Graph graph)
{
    vector<vector<int>> newGraph(graph.getSize()+1, vector<int>(graph.getSize()+1));
    for(int i = 0; i <= graph.getSize(); i++)
    {
        for(int j = 0; j <= graph.getSize(); j++)
        {
            if(i == graph.getSize() || j == graph.getSize())
            {
                newGraph[i][j] = 1;
            }
            else
            {
                newGraph[i][j] = graph.getEdge(i, j);
            }
        }
    }

    ariel::Graph g;
    g.loadGraph(newGraph, graph.getIsDirected());
    int start = graph.getSize();
    vector<int> parent(g.getSize());
    vector<int> distance(g.getSize());

    for(int i = 0; i < g.getSize(); i++)
    {
        distance[i] = INF;
        parent[i] = null;
    }
    distance[start] = 0;
    for(int i = 0; i < g.getSize() - 1; i++)
    {
        for(int u = 0; u < g.getSize(); u++)
        {
            for(int v = 0; v < g.getSize(); v++)
            {
                relax(u, v, g, parent, distance);
            }
        }
    }
    vector<int> cycle;
    for(int u = 0; u < g.getSize(); u++)
    {
        for(int v = 0; v < g.getSize(); v++)
        {
            if(g.getEdge(u, v) != 0 && distance[v] > distance[u] + g.getEdge(u, v)) //negative cycle
            {
                cycle.push_back(v);
                int x = parent[u];
                while(findX(cycle,x) != 0)
                {
                    cycle.push_back(x);
                    x = parent[x];
                }
                for(int i = 0; i < cycle.size(); i++)
                {
                    cout << cycle[i] << " -> ";
                }
                return;
            }   
        }
    }
    cout << "There is no negative cycle in the graph" << endl;
}

void ariel::Algorithms::isContainsCycle(Graph graph)
{
    vector<int> parent(graph.getSize());
    vector<int> distance(graph.getSize());
    vector<int> color(graph.getSize());
    for(int i = 0; i < graph.getSize(); i++)
    {
        color[i] = WHITE;
        parent[i] = null;
    }
    int time = 0;
    int Vertex = -1;
    for(int i = 0; i < graph.getSize(); i++)
    {
        if(color[i] == WHITE)
        {
            Vertex = DFSVisit(graph, i, parent, color, time);
            if(Vertex != -1) // there is a cycle
            {
                vector<int> cycle;
                cycle.push_back(Vertex);
                int x = parent[Vertex];
                while(findX(cycle,x) == 0)
                {
                    cycle.push_back(x);
                    x = parent[x];
                }
                for(int i = cycle.size()-1; i > 0; i++)
                {
                    cout << cycle[i] << "->";
                }
                cout << cycle[0] << endl;
                return;
                
            }
        }
    }
    cout << "There is no cycle in the graph" << endl;
}

void ariel::Algorithms::isBipartite(Graph graph)
{
    int start = 0;
    vector<int> parent(graph.getSize());
    vector<int> color(graph.getSize());
    for(int i = 0; i < graph.getSize(); i++)
    {
        color[i] = WHITE;
        parent[i] = null;
    }
    color[start] = BLUE;
    parent[start] = null;
    queue<int> q;
    q.push(start);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        
        for(int v = 0; v < graph.getSize(); v++)
        {
            if(graph.getEdge(u, v) != 0)
            {
                if(color[v] == color[u]){
                    cout << "The graph is not bipartite" << endl;
                    return;
                }
                if(color[v] == WHITE)
                {
                    parent[v] = u;
                    if(color[u] == BLUE)
                    {
                        color[v] = RED;
                    }
                    else
                    {
                        color[v] = BLUE;
                    }
                    
                    q.push(v);
                }
            }
        }
    }

    
    vector<int> setA;
    vector<int> setB;
    cout << "The graph is bipartite: ";
    for(int i = 0; i < graph.getSize(); i++)
    {
        if(color[i] == BLUE)
        {
            setA.push_back(i);
        }
        else
        {
            setB.push_back(i);
        }
    }
    cout << "A={";
    for(int i = 0; i < setA.size(); i++)
    {
        if(i == setA.size()-1)
        {
            cout << setA[i] << "}, B={";
        }
        else
        {
            cout << setA[i] << ", ";
        }
    }
    for(int i = 0; i < setB.size(); i++)
    {
        if(i == setB.size()-1)
        {
            cout << setB[i] << "}" << endl;
        }
        else
        {
        cout << setB[i] << ", ";
        }
    }
}

int ariel::Algorithms::DFSVisit(Graph &graph, int u, vector<int> &parent, vector<int> &color, int time)
{
    color[u] = GRAY;
    time++;
    for(int v = 0; v < graph.getSize(); v++)
    {
        if(graph.getEdge(u, v) != 0)
        {
            if(color[v] == WHITE)
            {
                parent[v] = u;
                DFSVisit(graph, v, parent, color, time);
            }
            else if(color[v] == GRAY)
            {
                return v;
            }
        }
    }
    color[u] = BLACK;
    time++;
    return -1;
}

void ariel::Algorithms::bfs(Graph &graph, int start, vector<int> &parent, vector<int> &distance)
{
    vector<int> color(graph.getSize(), WHITE);
    for(int i = 0; i < graph.getSize(); i++)
    {
        parent[i] = null;
        distance[i] = INF;
        color[i] = WHITE;
    }
    color[start] = GRAY;
    distance[start] = 0;
    parent[start] = null;
    queue<int> q;
    q.push(start);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int v = 0; v < graph.getSize(); v++)
        {
            if(graph.getEdge(u, v) != 0)
            {
                if(color[v] == WHITE)
                {
                    color[v] = GRAY;
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        color[u] = BLACK;
    }
}

void ariel::Algorithms::dijkstra(Graph &graph, int start, vector<int> &parent, vector<int> &distance)
{
    vector<int> color(graph.getSize());
    for(int i = 0; i < graph.getSize(); i++)
    {
        parent[i] = null;
        distance[i] = INF;
        color[i] = WHITE;
    }
    distance[start] = 0;
    for(int i = 0; i < graph.getSize(); i++)
    {
        int u = -1;
        u = extractMin(color, distance, u); // gets the vertex with the minimum distance that still not visited
        color[u] = BLACK;
        for(int v = 0; v < graph.getSize(); v++)
        {
            relax(u, v, graph, parent, distance);
        }
    }
}

int ariel::Algorithms::bellmanFord(Graph &graph, int start, vector<int> &parent, vector<int> &distance){
    for(int i = 0; i < graph.getSize(); i++)
    {
        distance[i] = INF;
        parent[i] = null;
    }
    distance[start] = 0;
    for(int i = 0; i < graph.getSize() - 1; i++)
    {
        for(int u = 0; u < graph.getSize(); u++)
        {
            for(int v = 0; v < graph.getSize(); v++)
            {
                relax(u, v, graph, parent, distance);
            }
        }
    }
    for(int u = 0; u < graph.getSize(); u++)
    {
        for(int v = 0; v < graph.getSize(); v++)
        {
            if(graph.getEdge(u, v) != 0 && distance[v] > distance[u] + graph.getEdge(u, v))
            {
                return failue;
            }
        }
    }
    return success;
}

int ariel::Algorithms::extractMin(vector<int> &color, vector<int> &distance, int u)
{
    u = -1;
    for(int i = 0; i < color.size(); i++)
    {
        if(color[i] == WHITE && (u == -1 || distance[i] < distance[u]))
        {
            u = i;
        }
    }
}

void ariel::Algorithms::relax(int u, int v, Graph &graph, vector<int> &parent, vector<int> &distance)
{
    if(graph.getEdge(u, v) != 0 && distance[v] > distance[u] + graph.getEdge(u, v))
    {
        distance[v] = distance[u] + graph.getEdge(u, v);
        parent[v] = u;
    }
}

int ariel::Algorithms::findX(vector<int> &parent, int x)
{
    for(int i = 0; i < parent.size(); i++)
    {
        if(parent[i] == x)
        {
            return 1;
        }
    }
    return 0;
}
