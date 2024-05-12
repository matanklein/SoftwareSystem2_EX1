/*
    ID: 8240
    Mail: matank214@gmail.com
*/

#include "Graph.hpp"

#define no_weights 0
#define Nonnegative_weights 1
#define negative_weight 2

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define RED 3
#define BLUE 4

#define null -1

#define INF 2147483647

#define failue -1
#define success 1

using namespace std;

namespace ariel
{
    class Algorithms
    {

    private:
        static void bfs(const Graph &graph, size_t start, vector<int> &parent, vector<int> &distance);
        static int bellmanFord(const Graph &graph, size_t start, vector<int> &parent, vector<int> &distance);
        static void dijkstra(const Graph &graph, size_t start, vector<int> &parent, vector<int> &distance);
        static void relax(size_t u, size_t v,const Graph &graph, vector<int> &parent, vector<int> &distance);
        static int extractMin(vector<int> &color, vector<int> &distance, int u);
        static int findNodeInVector(vector<int> &parent, int x);
        static int DFSVisit(const Graph &graph, size_t u, vector<int> &parent, vector<int> &color);

    public:
        static bool isConnected(const ariel::Graph &graph);
        static int shortestPath(const ariel::Graph &graph, int start, int end);
        static bool isContainsCycle(const ariel::Graph &graph);
        static bool isBipartite(const ariel::Graph &graph);
        static bool negativeCycle(const ariel::Graph &graph);
    };
}