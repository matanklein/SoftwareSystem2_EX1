#
#    ID: 8240
#    Mail: matank214@gmail.com
#

Graph:=
    Description: class that represents a graph.

    Data members:
        * vector<vector<int>> graph - represents the graph as a 2D matrix.

        * size_t size - number of vertices.

        * bool isDirected - represents if the graph is directed(true) or not directed(false).

        * int weihgt - represents if the graph is no-weighted/non-negative-weighted/negative-weighted.
        

    Methods:
        * Graph() - empty constructor.

        * ~Graph() - empty destructor.

        * void loadGraph(vector<vector<int>>, bool isdirec= true) - load the given graph in the data member and if the graph is directed.

        Throw error if the graph is not squre matrix or if the graph is not directed and the edge (i,j) != (j,i) for all i,j that are vertices.

        * void printGraph() - print how much vertices and edges there are. 

        * size_t getSize() - return the data number size.

        * int getEdge(size_t i, size_t j) - return the edge (i,j), 0 if the edge doesn't exit.

        * bool getIsDirected() - return the data member isDirected.

        * int getEdges() - return how many edges exits in the graph.

        * int getWeight() - return which weight is the graph.


Algorithms:=
    Description: class that represents algorithms on graph.

    Data members: None

    Methods:
        * static void isConnected(const ariel::Graph &graph) - if the graph is directed, do BFS on the graph and check for each vertex if all the vertices are reachable(distance != INF), else do BFS for all the vertices and check if all the vertices are reachable.

        * static void shortestPath(const ariel::Graph &graph, int start, int end, int algo = negative_weight) - if the graph is negative weighted run Bellman Ford, if it's weighted then run dijkstra, if the graph is not weighted then run BFS. return the weight of the shortest path, INF if it's not reachable or the graph contains negative cycle.

        * static void isContainsCycle(const ariel::Graph &graph) - run a similar DFS on the graph until we met a vertex twice(aka GRAY), if so take that vertex and start going backward(aka parent[v]) until we reach a vetex twice and prints the path. If we don't meet vertex twice then print that there isn't a cycle in the graph.

        * static void isBipartite(const ariel::Graph &graph) - will run a BFS and color the vertex in blue and red so that each parent will color its child in different color of his color, if two neighbors are in the same color prints that there isn't a bipartite , else will prints a 2 sets that represent a Bipartite.

        * static void negativeCycle(const ariel::Graph &graph) - will add extra vertex and run a Bellman-Ford, if we can relax an edge again (after the Bellman-ford)then take one of the vertices and run for his parents until we get the same vertex twice and print that path, else return that there isn't negativeCycle.