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

#define INF 1000000

#define failue -1
#define success 1

using namespace std;

namespace ariel
{
    class Algorithms
    {

    private:
        static void bfs(Graph &graph, int start, vector<int> &parent, vector<int> &distance);
        static int bellmanFord(Graph &graph, int start, vector<int> &parent, vector<int> &distance);
        static void dijkstra(Graph &graph, int start, vector<int> &parent, vector<int> &distance);
        static void relax(int u, int v, Graph &graph, vector<int> &parent, vector<int> &distance);
        static int extractMin(vector<int> &color, vector<int> &distance, int u);
        static int findX(vector<int> &parent, int x);
        static int DFSVisit(Graph &graph, int u, vector<int> &parent, vector<int> &color, int time);

    public:
        static int isConnected(ariel::Graph graph); //Done
        static void shortestPath(ariel::Graph graph, int start, int end, int algo = negative_weight); //Done
        static void isContainsCycle(ariel::Graph graph);
        static void isBipartite(ariel::Graph graph);
        static void negativeCycle(ariel::Graph graph); //Done
    };
}