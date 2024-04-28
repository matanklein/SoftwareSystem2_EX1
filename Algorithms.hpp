#include "Graph.hpp"
#define no_weights 0
#define Nonnegative_weights 1
#define negative_weight 2
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define null -1
#define INF 1000000
#define failue -1
#define success 1

using namespace std;

namespace ariel
{
    class Algorithms
    {

    private:
        void bfs(Graph &graph, int start, vector<int> &parent, vector<int> &distance);
        int bellmanFord(Graph &graph, int start, vector<int> &parent, vector<int> &distance);
        void dijkstra(Graph &graph, int start, vector<int> &parent, vector<int> &distance);
        void relax(int u, int v, Graph &graph, vector<int> &parent, vector<int> &distance);
        int extractMin(vector<int> &color, vector<int> &distance, int u);

    public:
        bool isConnected(Graph &graph);
        string shortestPath(Graph &graph, int start, int end, int algo = negative_weight);
        bool isContainsCycle(Graph &graph);
        string isBipartite(Graph &graph);
        void negativeCycle(Graph &graph);
    };
}