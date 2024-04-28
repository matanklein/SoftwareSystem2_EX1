#include "Algorithms.hpp"
#include <queue>

string ariel::Algorithms::shortestPath(Graph &graph, int start, int end, int algo)
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
            return "Negative cycle detected";
        }
    }
    if(distance[end] == INF)
    {
        return "-1";
    }
    string path = "";
    int u = end;
    while(u != null)
    {
        path = to_string(u) + " -> " + path;
        u = parent[u];
    }
    return path;
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
