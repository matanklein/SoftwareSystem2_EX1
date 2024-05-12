/*
    ID: 8240
    Mail: matank214@gmail.com
*/

#include "Algorithms.hpp"
#include <queue>
#include <iostream>

int ariel::Algorithms::shortestPath(const Graph &graph, int start, int end)
{
    int algo = graph.getWeight();
    vector<int> parent(graph.getSize());
    vector<int> distance(graph.getSize());
    if(algo == no_weights)
    {
        bfs(graph, (size_t)start, parent, distance);
    }
    else if(algo == Nonnegative_weights)
    {
        dijkstra(graph, (size_t)start, parent, distance);
    }
    else if(algo == negative_weight)
    {
        if(bellmanFord(graph, (size_t)start, parent, distance) == failue)
        {
            cout << "Negative cycle detected" << endl;
            return INF;
        }
    }
    if(distance[(size_t)end] == INF)
    {
        cout << "There is no path between " << start << " and " << end << endl;
        return INF;
    }
    vector<int> q;
    int u = end;
    while(u != null) // gets the path from the end to the start
    {
        q.push_back(u);
        u = parent[(size_t)u];
    }
    for(size_t i = q.size()-1; i >= 0; i--)
    {
        if(i == 0){
            cout << q[i] << endl;
            return distance[(size_t)end];
        }
        cout << q[i] << "->";
    }
}

bool ariel::Algorithms::isConnected(const Graph &graph)
{
    if(graph.getSize() == 0)
    {
        cout << "The graph is connected" << endl;
        return true;
    }
    vector<int> parent(graph.getSize());
    vector<int> distance(graph.getSize());
    if(graph.getIsDirected())
    {
        bool onceConnected = false;
        for(size_t i = 0; i < graph.getSize(); i++)
        {
            onceConnected = true;
            bfs(graph, i, parent, distance);
            for(size_t j = 0; j < graph.getSize(); j++)
            {
                if(distance[j] == INF) // if there is a vertex that is not connected to the current vertex
                {
                    onceConnected = false;
                    break;
                }
            }
            if(onceConnected)
            {
                cout << "The graph is connected" << endl;
                return true;
            }
        }
        cout << "The graph is not connected" << endl;
        return false;
    }
    else // undirected graph
    {
        bfs(graph, 0, parent, distance);
        for(size_t i = 0; i < graph.getSize(); i++)
        {
            if(distance[i] == INF)
            {
                cout << "The graph is not connected" << endl;
                return false;
            }
        }
    }
    cout << "The graph is connected" << endl;
    return true;
}

bool ariel::Algorithms::negativeCycle(const Graph &graph)
{
    // adds a new vertex that connects to all the other vertices with weight 1
    vector<vector<int>> newGraph(graph.getSize()+1, vector<int>(graph.getSize()+1));
    for(size_t i = 0; i <= graph.getSize(); i++)
    {
        for(size_t j = 0; j <= graph.getSize(); j++)
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
    size_t start = graph.getSize();
    vector<int> parent(g.getSize(), null);
    vector<int> distance(g.getSize(), INF);

    distance[start] = 0;
    for(size_t i = 0; i < g.getSize() - 1; i++)
    {
        for(size_t u = 0; u < g.getSize(); u++)
        {
            for(size_t v = 0; v < g.getSize(); v++)
            {
                relax(u, v, g, parent, distance);
            }
        }
    }
    vector<int> cycle;
    for(size_t u = 0; u < g.getSize(); u++)
    {
        for(size_t v = 0; v < g.getSize(); v++)
        {
            if(g.getEdge(u, v) != 0 && distance[v] > distance[u] + g.getEdge(u, v)) //negative cycle
            {
                cycle.push_back(v);
                int x = parent[v];
                while(findNodeInVector(cycle,x) == false)
                {
                    cycle.push_back(x);
                    x = parent[(size_t)x];
                }
                for(size_t i = 0; i < cycle.size(); i++)
                {
                    if(i == cycle.size()-1)
                    {
                        cout << cycle[i];
                        cout << "->" << cycle[0] << endl;
                    }
                    else
                    {
                        cout << cycle[i] << "->";
                    }
                }
                return true;
            }   
        }
    }
    cout << "There is no negative cycle in the graph" << endl;
    return false;
}


bool ariel::Algorithms::isContainsCycle(const Graph &graph)
{
    vector<int> parent(graph.getSize(),null);
    vector<int> color(graph.getSize(),WHITE);
    int Vertex = -1;
    for(size_t i = 0; i < graph.getSize(); i++)
    {
        if(color[i] == WHITE)
        {
            Vertex = DFSVisit(graph, i, parent, color);
            if(Vertex != -1) // there is a cycle
            {
                vector<int> cycle;
                cycle.push_back(Vertex);
                int current = parent[(size_t)Vertex];
                while(findNodeInVector(cycle,current) == false) // gets the cycle
                {
                    cycle.push_back(current);    
                    current = parent[(size_t)current];
                }
                for(size_t i = cycle.size()-1; i > 0; i--)
                {
                    cout << cycle[i] << "->";
                }
                cout << cycle[0] << "->" << cycle[cycle.size()-1] << endl;
                return true;
            }
        }
    }
    cout << "There is no cycle in the graph" << endl;
    return false;
}

bool ariel::Algorithms::isBipartite(const Graph &graph)
{
    size_t start = 0;
    vector<int> parent(graph.getSize());
    vector<int> color(graph.getSize());
    for(size_t i = 0; i < graph.getSize(); i++)
    {
        color[i] = WHITE;
        parent[i] = null;
    }
    color[start] = BLUE;
    parent[start] = null;
    queue<size_t> q;
    q.push(start);
    while(!q.empty())
    {
        size_t u = q.front();
        q.pop();
        
        for(size_t v = 0; v < graph.getSize(); v++)
        {
            if(graph.getEdge(u, v) != 0)
            {
                if(color[v] == color[u]){ // if the two vertices that connected have the same color
                    cout << "The graph is not bipartite" << endl;
                    return false;
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

    // prints the bipartite graph.
    vector<int> setA;
    vector<int> setB;
    cout << "The graph is bipartite: ";
    for(size_t i = 0; i < graph.getSize(); i++)
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
    for(size_t i = 0; i < setA.size(); i++)
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
    for(size_t i = 0; i < setB.size(); i++)
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
    return true;
}

int ariel::Algorithms::DFSVisit(const Graph &graph, size_t u, vector<int> &parent, vector<int> &color)
{
    color[u] = GRAY;
    for(size_t v = 0; v < graph.getSize(); v++)
    {
        if(graph.getEdge(u, v) != 0)
        {
            
            if(graph.getIsDirected() == false && parent[u] == v)
            {
                continue;
            }
            if(color[v] == GRAY)
            {   
                parent[v] = u;
                return v;
            }
            else if(color[v] == WHITE)
            {
                parent[v] = u;
                int ans = DFSVisit(graph, v, parent, color);
                if(ans != -1)
                {
                    return ans;
                }
            }
             
        }
    }
    color[u] = BLACK;
    return -1;
}

void ariel::Algorithms::bfs(const Graph &graph, size_t start, vector<int> &parent, vector<int> &distance)
{
    vector<int> color(graph.getSize(), WHITE);
    for(size_t i = 0; i < graph.getSize(); i++)
    {
        parent[i] = null;
        distance[i] = INF;
        color[i] = WHITE;
    }
    color[start] = GRAY;
    distance[start] = 0;
    parent[start] = null;
    queue<size_t> q;
    q.push(start);
    while(!q.empty())
    {
        size_t u = q.front();
        q.pop();
        for(size_t v = 0; v < graph.getSize(); v++)
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

void ariel::Algorithms::dijkstra(const Graph &graph, size_t start, vector<int> &parent, vector<int> &distance)
{
    vector<int> color(graph.getSize());
    for(size_t i = 0; i < graph.getSize(); i++)
    {
        parent[i] = null;
        distance[i] = INF;
        color[i] = WHITE;
    }
    distance[start] = 0;
    for(size_t i = 0; i < graph.getSize(); i++)
    {
        int u = -1;
        u = extractMin(color, distance, u); // gets the vertex with the minimum distance that still not visited
        color[(size_t)u] = BLACK;
        for(size_t v = 0; v < graph.getSize(); v++)
        {
            relax((size_t)u, v, graph, parent, distance);
        }
    }
}

int ariel::Algorithms::bellmanFord(const Graph &graph, size_t start, vector<int> &parent, vector<int> &distance){
    for(size_t i = 0; i < graph.getSize(); i++)
    {
        distance[i] = INF;
        parent[i] = null;
    }
    distance[start] = 0;
    for(size_t i = 0; i < graph.getSize() - 1; i++)
    {
        for(size_t u = 0; u < graph.getSize(); u++)
        {
            for(size_t v = 0; v < graph.getSize(); v++)
            {
                relax(u, v, graph, parent, distance);
            }
        }
    }
    for(size_t u = 0; u < graph.getSize(); u++)
    {
        for(size_t v = 0; v < graph.getSize(); v++)
        {
            if(graph.getEdge(u, v) != 0 && distance[v] > distance[u] + graph.getEdge(u, v)) //negative cycle
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
    for(size_t i = 0; i < color.size(); i++)
    {
        if(color[i] == WHITE && (u == -1 || distance[i] < distance[(size_t)u])) // gets the vertex with the minimum distance that still not visited
        {
            u = i;
        }
    }
    return u;
}

void ariel::Algorithms::relax(size_t u, size_t v, const Graph &graph, vector<int> &parent, vector<int> &distance)
{
    if(distance[u] == INF)
    {
        return;
    }
    if(graph.getEdge(u, v) != 0 && (distance[v] > distance[u] + graph.getEdge(u, v) || distance[v] == INF))
    {
        distance[v] = distance[u] + graph.getEdge(u, v);
        parent[v] = u;
    }
}

int ariel::Algorithms::findNodeInVector(vector<int> &vec, int x)
{
    for(size_t i = 0; i < vec.size(); i++)
    {
        if(vec[i] == x)
        {
            return true;
        }
    }
    return false;
}
