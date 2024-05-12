/*
    ID: 8240
    Mail: matank214@gmail.com
*/

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0}};
    CHECK_THROWS(g.loadGraph(graph2, false));
}

TEST_CASE("Test getSize")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
   
    CHECK(g.getSize() == 3);
}
TEST_CASE("Test getEdge")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getEdge(0, 1) == 1);
    CHECK(g.getEdge(1, 2) == 1);
    CHECK(g.getEdge(2, 0) == 0);
}
TEST_CASE("Test getIsDirected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getIsDirected() == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2, false);
    CHECK(g.getIsDirected() == false);
}

TEST_CASE("Test getEdges")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getEdges() == 4);

    g.loadGraph(graph, false);
    CHECK(g.getEdges() == 2);
}

TEST_CASE("Test loadGraph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getEdge(0, 1) == 1);
    CHECK(g.getEdge(1, 2) == 1);
    CHECK(g.getEdge(2, 0) == 0);
    CHECK(g.getSize() == 3);
    CHECK(g.getIsDirected() == true);
    CHECK(g.getEdges() == 4);
    CHECK(g.getWeight() == 1);
}

TEST_CASE("Test isConnected"){
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph3 = {
        {0, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0}};
    g.loadGraph(graph3, false);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph4 = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph4, false);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath"){
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == 2);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == INF);

    vector<vector<int>> graph3 = {
        {0, 8, 3, 2, 12},
        {8, 0, 0, 0, 0},
        {3, 0, 0, 0, 0},
        {2, 0, 0, 0, 0},
        {12, 0, 0, 0, 0}};
    g.loadGraph(graph3, false);
    CHECK(ariel::Algorithms::shortestPath(g, 1, 4) == 20);

    vector<vector<int>> graph4 = {
        {0, 11, 5, 0},
        {12, 0, 0, 0},
        {0, 0, 0, 3},
        {0, 2, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == 10);

    vector<vector<int>> graph5 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, -1, 0},
        {1, 1, 0, 1, 0},
        {0, -1, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == INF);

    vector<vector<int>> graph6 = {
        {0, 3, 0, 5, 0},
        {0, 0, 2, 0, 0},
        {-1, 0, 0, -2, 0},
        {0, 0, 0, 0, 3},
        {0, 2, 0, 0, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == 6);
}

TEST_CASE("Test isContainsCycle"){
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, false);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);
}

TEST_CASE("Test isBipartite"){
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0}};
    g.loadGraph(graph2,false);
    CHECK(ariel::Algorithms::isBipartite(g) == false);

    vector<vector<int>> graph3 = {
        {0, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0}};
    g.loadGraph(graph3,false);
    CHECK(ariel::Algorithms::isBipartite(g) == true);
}

TEST_CASE("Test negativeCycle"){
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 5, 0, 0, 0},
        {0, 0, -3, 0, 0},
        {0, 0, 0, 1, 5},
        {2, 1, 0, 0, 0},
        {0, 0, 0, -2, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) == true);
}